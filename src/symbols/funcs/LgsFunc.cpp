#include "funcs/LgsFunc.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "../codegen/LgsCodeGenVisitor.h"
#include "types/LgsFuncType.h"
#include "types/LgsVoid.h"
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Module.h>

Value* LgsFunc::call(LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args) {
    if (funcType->hasDefaults) assert(0);
    std::vector<Value*> IRArgs;
    for (int i = funcType->isStatic; i < funcType->params.size(); ++i) {
        auto arg = args[i];
        const auto& param = funcType->params[i];
        if (!param.isSelf) {
            arg = arg->castTo(param.type);
        }
        auto v = arg->IRValue;
        v = loadIRArg(&codeGen, v, arg->type);
        IRArgs.push_back(v);
        if (!param.isSelf && args[i] != arg) {
            freeExpr(arg);
        }
    }
    return callIR(codeGen, IRArgs);
}

Value* LgsFunc::loadIRArg(LgsCodeGen* codeGen, Value* v, LgsType* type) {
    if (type->asCPtr() || type->asFuncType() || type->asObject() || type->asDArray() || type->asSArray()) return v;
    const auto vTy = v->getType();
    if (vTy->isIntegerTy() || vTy->isFloatingPointTy()) return v;
    if (!vTy->isPointerTy()) return v;
    if (isa<GlobalVariable>(v) || isa<LoadInst>(v)) return v;
    const auto ty = type->getIRType(*codeGen);
    return codeGen->builder.CreateLoad(ty, v);
}

Function* LgsFunc::getIRFunc(LgsCodeGen& codeGen) {
    auto funcName = funcType->getName();
    auto IRFunc = codeGen.IRModule->getFunction(funcName);
    if (IRFunc) return IRFunc;
    const auto type = funcType->getIRType(codeGen);
    const auto funcTy = llvm::cast<FunctionType>(type);
    if (funcType->isInternal) {
        funcName = LGS_RUNTIME_NAMES_PREFIX + funcName;
    }
    IRFunc = codeGen.getFunc(funcName, funcTy);
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

Value* LgsFunc::callIR(LgsCodeGen& codeGen, const std::vector<Value*>& args) {
    CallInst* rv = nullptr;
    if (IRValue) {
        const auto funcTypeIR = funcType->getIRType(codeGen);
        const auto IRFuncType = llvm::cast<FunctionType>(funcTypeIR);
        rv = codeGen.builder.CreateCall(IRFuncType, IRValue, args);
    } else {
        const auto IRFunc = getIRFunc(codeGen);
        rv = codeGen.builder.CreateCall(IRFunc, args);
    }
    return rv;
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

BasicBlock* LgsFunc::getCleanupBlock(LgsCodeGen& codeGen) {
    if (cleanupBlock) return cleanupBlock;
    cleanupBlock = codeGen.createBlock(BLOCK_NAME_CLEANUP);
    return cleanupBlock;
}

bool LgsFunc::needsCleanup() const {
    return !heapAllocExprs.empty();
}

std::string LgsFunc::pname() {
    return funcType->pname();
}

json::value LgsFunc::asJSON() {
    json::object obj;
    obj["funcType"] = funcType->asJSON();
    obj["stmtsBlock"] = stmtsBlock->asJSON();
    return obj;
}

LgsExpr* LgsFunc::clone() {
    const auto newFunc = new LgsFunc(funcType->clone()->asFuncType());
    newFunc->isNull = isNull;
    newFunc->isSpread = isSpread;
    return newFunc;
}

void LgsFunc::setDebugValue(LgsCodeGen& codeGen) {
    const auto diBuilder = codeGen.diBuilder;
    const auto dbInt32 = funcType->rt->getDebugType(codeGen);
    const auto parameterTypes = diBuilder->getOrCreateTypeArray({dbInt32});
    const auto subroutine = diBuilder->createSubroutineType(parameterTypes);
    codeGen.diProgram = diBuilder->createFunction(
        codeGen.compileUnit,
        funcType->name,
        "",
        codeGen.diFile,
        location.lineStart,
        subroutine,
        location.lineStart
    );
    getIRFunc(codeGen)->setSubprogram(codeGen.diProgram);
    codeGen.builder.SetCurrentDebugLocation(getDebugLoc(codeGen));
}

LgsFunc::~LgsFunc() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
}
