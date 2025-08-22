#include "funcs/LgsFunc.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsReturn.h"
#include "types/LgsFuncType.h"
#include "types/LgsVoid.h"
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Module.h>

void LgsFunc::createIRValue(LgsCodeGen* codeGen) {
    codeGen->savedIP = codeGen->builder.saveIP();
    generateIR(codeGen);
    codeGen->builder.restoreIP(codeGen->savedIP);
    IRValue = getIRFunc(codeGen);
}

Value* LgsFunc::call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) {
    if (funcType->hasDefaults) {
        assert(0);
    }
    std::vector<Value*> IRArgs;
    for (int i = funcType->isStatic; i < args.size(); ++i) {
        auto arg = loadIRArg(codeGen, args[i]->getIRValue(codeGen), args[i]->type);
        IRArgs.push_back(arg);
    }
    return callIR(codeGen, IRArgs);
}

void LgsFunc::generateIR(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this);
    createPrologue(codeGen);
    stmtsBlock->createIRValue(codeGen);
    createEpilogue(codeGen);
    if (!codeGen->lastInstTerminator()) codeGen->builder.CreateRetVoid();
    codeGen->stack.exitScope();
}

Function* LgsFunc::getIRFunc(LgsCodeGen* codeGen) {
    auto funcName = funcType->getName();
    auto IRFunc = codeGen->IRModule->getFunction(funcName);
    if (IRFunc) return IRFunc;
    const auto type = funcType->getIRType(codeGen);
    const auto funcTy = cast<FunctionType>(type);
    if (funcType->isInternal) {
        funcName = LGS_RUNTIME_NAMES_PREFIX + funcName;
    }
    IRFunc = codeGen->getFunc(funcName, funcTy);
    if (funcType->params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (int i = funcType->isStatic; i < funcType->params.size(); ++i) {
        auto& param = funcType->params[i];
        param.setIRValue(args);
        args->setName(param.name);
        args++;
    }
    return IRFunc;
}

Value* LgsFunc::callIR(LgsCodeGen* codeGen, const std::vector<Value*>& args) {
    CallInst* rv = nullptr;
    if (IRValue) {
        const auto funcTypeIR = funcType->getIRType(codeGen);
        const auto IRFuncType = cast<FunctionType>(funcTypeIR);
        rv = codeGen->builder.CreateCall(IRFuncType, IRValue, args);
    } else {
        const auto IRFunc = getIRFunc(codeGen);
        rv = codeGen->builder.CreateCall(IRFunc, args);
    }
    return rv;
}

Value* LgsFunc::loadIRArg(LgsCodeGen* codeGen, Value* v, LgsType* type) {
    if (type->asCPtr() || type->asFuncType() || type->asObject() || type->asDArray() || type->asSArray()) return v;
    const auto vTy = v->getType();
    if (vTy->isIntegerTy() || vTy->isFloatingPointTy()) return v;
    if (!vTy->isPointerTy()) return v;
    if (isa<GlobalVariable>(v) || isa<LoadInst>(v)) return v;
    const auto ty = type->getIRType(codeGen);
    return codeGen->builder.CreateLoad(ty, v);
}

void LgsFunc::createPrologue(LgsCodeGen* codeGen) {
    const auto IRFunc = getIRFunc(codeGen);
    IRFunc->setLinkage(funcType->isPublic ? GlobalValue::ExternalLinkage : GlobalValue::PrivateLinkage);
    const auto entryBlock = codeGen->createBlock(BLOCK_NAME_ENTRY, IRFunc);
    codeGen->builder.SetInsertPoint(entryBlock);
    codeGen->callStackPush();
}

void LgsFunc::createEpilogue(LgsCodeGen* codeGen) {
    if (hasDefers) codeGen->callDefers();
    if (needsCleanup()) {
        cleanupExprs(codeGen);
    }
    codeGen->callPopStack();
}

void LgsFunc::initFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops) {
    funcType = new LgsFuncType();
    funcType->name = name;
    funcType->rt = rt;
    funcType->setFuncOptions(ops);
    if (funcType->isMethod && !funcType->isStatic) {
        funcType->parentName = paramTypes.front()->getName();
    }
    for (const auto paramsType : paramTypes) {
        funcType->params.push_back(LgsParam(paramsType));
    }
    type = funcType;
}

bool LgsFunc::needsCleanup() const {
    return !heapAllocExprs.empty();
}

void LgsFunc::cleanupExprs(LgsCodeGen* codeGen) {
    codeGen->branchAndStartBlock(getCleanupBlock(codeGen));
    const auto currentFunc = codeGen->stack.currentFunc();
    if (returnExpr && codeGen->stack.isRootScope()) {
        const auto IRReturnType = currentFunc->funcType->rt->getIRType(codeGen);
        const auto returnPhiNode = codeGen->builder.CreatePHI(IRReturnType, currentFunc->returnStmts.size());
        for (const auto returnStmt : currentFunc->returnStmts) {
            returnPhiNode->addIncoming(returnStmt->expr->getIRValue(codeGen), returnStmt->parentBlock);
        }
        for (const auto expr : heapAllocExprs) {
            expr->type->freeValue(codeGen, expr->getIRValue(codeGen));
        }
        codeGen->builder.CreateRet(returnPhiNode);
    } else {
        for (const auto expr : heapAllocExprs) {
            expr->type->freeValue(codeGen, expr->getIRValue(codeGen));
        }
        if (returnExpr) {
            // const auto stmtsBlock = codeGen->stack.parentBlock();
            // codeGen->builder.CreateBr(stmtsBlock->getCleanupBlock(codeGen));
        }
    }
}

BasicBlock* LgsFunc::getCleanupBlock(LgsCodeGen* codeGen) {
    if (cleanupBlock) return cleanupBlock;
    cleanupBlock = codeGen->createBlock(BLOCK_NAME_CLEANUP);
    return cleanupBlock;
}

void LgsFunc::createDebugValue(LgsCodeGen* codeGen) {
    const auto& [diFile, diBuilder, compileUnit] = codeGen->debugger;
    const auto dbInt32 = diBuilder->createBasicType("int", 32, dwarf::DW_ATE_signed);
    const auto subroutine = diBuilder->createSubroutineType(diBuilder->getOrCreateTypeArray({dbInt32}));
    const auto subprogram = diBuilder->createFunction(compileUnit, funcType->name, "", diFile, 1, subroutine, 1);
    getIRFunc(codeGen)->setSubprogram(subprogram);
    codeGen->builder.SetCurrentDebugLocation(DILocation::get(
        codeGen->context,
        location.lineStart,
        location.posInLine,
        subprogram,
        subprogram->getScope()
        ));
}

bool LgsFunc::completeType(LgsType* toType) {
    const auto otherFuncType = toType->asFuncType();
    if (!otherFuncType) return false;
    if (otherFuncType->params.size() != funcType->params.size()) return false;
    for (int i = 0; i < funcType->params.size(); ++i) {
        if (funcType->params[i].type) continue;
        funcType->params[i].type = otherFuncType->params[i].type;
    }
    if (!funcType->rt) {
        funcType->rt = otherFuncType->rt;
    }
    return true;
}

std::string LgsFunc::pname() {
    return funcType->pname();
}

json::value LgsFunc::asJSON() {
    json::object obj;
    obj["name"] = funcType->name;
    obj["rt"] = funcType->rt->asJSON();
    json::object funcConfigs;
    funcConfigs["isMethod"] = funcType->isMethod;
    funcConfigs["isPublic"] = funcType->isPublic;
    funcConfigs["isInternal"] = funcType->isInternal;
    funcConfigs["isVirtual"] = funcType->isVirtual;
    funcConfigs["isVariadic"] = funcType->isVariadic;
    funcConfigs["isStatic"] = funcType->isStatic;
    funcConfigs["isOptional"] = funcType->isOptional;
    funcConfigs["isTerminator"] = funcType->isTerminator;
    funcConfigs["isAnonymous"] = funcType->isLambda;
    funcConfigs["hasDefaults"] = funcType->hasDefaults;
    obj["configs"] = funcConfigs;
    json::array params;
    for (auto& param : funcType->params) {
        params.emplace_back(param.asJSON());
    }
    obj["params"] = params;
    obj["stmtsBlock"] = stmtsBlock->asJSON();
    return obj;
}

LgsExpr* LgsFunc::clone() {
    const auto newFunc = new LgsFunc(funcType->clone()->asFuncType());
    newFunc->isNull = isNull;
    newFunc->isSpread = isSpread;
    newFunc->isAssignable = isAssignable;
    return newFunc;
}

LgsFunc::~LgsFunc() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
}
