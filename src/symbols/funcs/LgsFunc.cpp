#include "funcs/LgsFunc.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "types/LgsFuncType.h"
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Module.h>

void LgsFunc::generateIR(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    createPrologue(codeGen);
    stmtsBlock->createIRValue(codeGen);
    createEpilogue(codeGen);
    if (!codeGen->lastInstTerminator()) codeGen->builder.CreateRetVoid();
    codeGen->stack.exitScope();
}

void LgsFunc::createIRValue(LgsCodeGen* codeGen) {
    codeGen->savedIP = codeGen->builder.saveIP();
    generateIR(codeGen);
    codeGen->builder.restoreIP(codeGen->savedIP);
    IRValue = getIRFunc(codeGen);
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

Value* LgsFunc::getIRArg(LgsCodeGen* codeGen, LgsExpr* arg) {
    const auto v = arg->getIRValue(codeGen);
    if (arg->type->asObject()) return v;
    if (arg->type->asDArray()) return v;
    if (!v->getType()->isPointerTy()) return v;
    if (v->getType()->isIntegerTy()) return v;
    if (isa<GlobalVariable>(v) || isa<LoadInst>(v)) return v;
    const auto ty = arg->type->getIRType(codeGen);
    return codeGen->builder.CreateLoad(ty, v);
}

Value* LgsFunc::call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) {
    std::vector<Value*> IRArgs;
    if (funcType->hasDefaults) {
        for (int i = funcType->isStatic; i < args.size(); ++i) {
            auto arg = getIRArg(codeGen, args[i]);
            IRArgs.push_back(arg);
        }
        const std::vector defaultParams(funcType->params.begin() + args.size(), funcType->params.end());
        for (const auto& defaultParam : defaultParams) {
            auto arg = defaultParam.expr->getIRValue(codeGen);
            IRArgs.push_back(arg);
        }
    } else {
        for (int i = funcType->isStatic; i < args.size(); ++i) {
            auto arg = getIRArg(codeGen, args[i]);
            IRArgs.push_back(arg);
        }
    }
    return callIR(codeGen, IRArgs);
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

void LgsFunc::createPrologue(LgsCodeGen* codeGen) {
    const auto IRFunc = getIRFunc(codeGen);
    IRFunc->setLinkage(funcType->isPublic ? GlobalValue::ExternalLinkage : GlobalValue::PrivateLinkage);
    const auto entryBlock = codeGen->createBlock(BLOCK_NAME_ENTRY, IRFunc);
    codeGen->builder.SetInsertPoint(entryBlock);
    codeGen->callStackPush();
}

void LgsFunc::createEpilogue(LgsCodeGen* codeGen) const {
    if (hasDefers) codeGen->callDefers();
    codeGen->callPopStack();
}

std::string LgsFunc::pname() {
    return funcType->pname();
}

void LgsFunc::createDebugValue(LgsCodeGen* codeGen) {
    const auto& debug = codeGen->debugger;
    const auto dbInt32 = debug.diBuilder->createBasicType("int", 32, dwarf::DW_ATE_signed);
    const auto subroutine = debug.diBuilder->createSubroutineType(debug.diBuilder->getOrCreateTypeArray({dbInt32}));
    const auto subprogram = debug.diBuilder->createFunction(debug.compileUnit, funcType->name, "", debug.diFile, 1, subroutine, 1);
    getIRFunc(codeGen)->setSubprogram(subprogram);
    codeGen->builder.SetCurrentDebugLocation(DILocation::get(
        codeGen->context,
        location.lineStart,
        location.posInLine,
        subprogram,
        subprogram->getScope()
    ));
}

bool LgsFunc::castTo(LgsType* toType) {
    const auto otherFuncType = toType->asFuncType();
    if (!otherFuncType) return false;
    funcType->rt = otherFuncType->rt;
    for (int i = 0; i < funcType->params.size(); ++i) {
        funcType->params[i].type = otherFuncType->params[i].type;
    }
    return true;
}

json::object LgsFunc::asJSON() {
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
    funcConfigs["isAnonymous"] = funcType->isAnonymous;
    funcConfigs["hasDefaults"] = funcType->hasDefaults;
    obj["configs"] = funcConfigs;
    json::array params;
    for (auto& param : funcType->params) {
        params.emplace_back(param.asJSON());
    }
    obj["params"] = params;
    obj["stmtsBlock"] = stmtsBlock->asJSON()["stmts"];
    return obj;
}

LgsFunc::~LgsFunc() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
}