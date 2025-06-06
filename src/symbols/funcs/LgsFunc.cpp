#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

void LgsFunc::generateIR(LgsRuntime* runtime) {
    runtime->stack.enterFunc(this);
    startBlockFunc(runtime);
    stmtBlock->createIRValue(runtime);
    if (funcType.rt->isVoid) {
        runtime->freeExprs();
        runtime->builder.CreateRetVoid();
    }
    runtime->stack.exitFunc();
}

Function* LgsFunc::getIRFunc(LgsRuntime* runtime) {
    const auto funcIRName = funcType.getIRName();
    auto IRFunc = runtime->module->getFunction(funcIRName);
    if (IRFunc) return IRFunc;
    const auto funcTy = dyn_cast<FunctionType>(funcType.getIRType());
    auto func = runtime->module->getOrInsertFunction(funcIRName, funcTy);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (funcType.swapReturn) {
        setBigObjAttrs(*IRFunc);
    }
    if (funcType.params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (const auto param : funcType.params) {
        param->setIRValue(args);
        args->setName(param->name);
        args++;
    }
    return IRFunc;
}

Value* LgsFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    if (funcType.hasDefaultParams) assert(false);
    if (funcType.isVariadic) assert(false);
    for (int i = funcType.isStatic; i < args.size(); ++i) {
        addIRArg(runtime, IRArgs, args[i]);
    }
    return callIR(runtime, IRArgs);
}

Value* LgsFunc::callIR(LgsRuntime* runtime, const vector<Value*>& args) {
    if (IRValue) {
        const auto IRFuncType = dyn_cast<FunctionType>(funcType.getIRType());
        return runtime->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(runtime);
    Value* rv;
    if (funcType.swapReturn) {
        const auto paramIRType = getReturnSwapParam()->type->getIRType();
        rv = runtime->builder.CreateAlloca(paramIRType);
        vector finalArgs(args.begin(), args.end());
        finalArgs.insert(finalArgs.begin() + funcType.returnParamIndex, rv);
        runtime->builder.CreateCall(IRFunc, finalArgs);
    } else {
        rv = runtime->builder.CreateCall(IRFunc, args);
    }
    return rv;
}

void LgsFunc::addIRArg(LgsRuntime* runtime, vector<Value*>& IRArgs, LgsExpr* arg) const {
    const auto argIRValue = arg->getIRValue(runtime);
    if (shouldLoadIRArg(argIRValue)) {
        const auto artIRType = arg->type->getIRType();
        const auto value = runtime->builder.CreateLoad(artIRType, argIRValue);
        IRArgs.emplace_back(value);
    } else {
        IRArgs.emplace_back(argIRValue);
    }
}

void LgsFunc::setBigObjAttrs(Function& IRFunc) const {
    const auto paramIRType = getReturnSwapParam()->type->getIRType();
    IRFunc.addParamAttr(funcType.returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::StructRet, paramIRType));
    IRFunc.addParamAttr(funcType.returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::Writable));
    IRFunc.addParamAttr(funcType.returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::NoAlias));
}

bool LgsFunc::shouldLoadIRArg(Value* value) const {
    if (isa<GlobalVariable>(value) || isa<LoadInst>(value)) return false;
    if (const auto alloca = dyn_cast<AllocaInst>(value)) {
        const auto allocatedType = alloca->getAllocatedType();
        return !allocatedType->isStructTy() && !allocatedType->isArrayTy();
    }
    if (value->getType()->isIntegerTy() || value->getType()->isFloatingPointTy()) {
        return false;
    }
    if (const auto gep = dyn_cast<GetElementPtrInst>(value)) {
        const auto source = gep->getSourceElementType();
        const auto results = gep->getResultElementType();
        const auto isArrayTy = source->isArrayTy();
        const auto isByteTy = results && results->isIntegerTy(8);
        return !isArrayTy || !isByteTy;
    }
    if (isa<ConstantExpr>(value)) {
        const auto constExpr = cast<ConstantExpr>(value);
        return constExpr->getOpcode() == Instruction::GetElementPtr;
    }
    return true;
}

LgsParam* LgsFunc::getReturnSwapParam() const {
    if (!funcType.swapReturn) assert(false);
    if (funcType.returnParamIndex > funcType.params.size()) assert(false);
    return funcType.params[funcType.returnParamIndex];
}

void LgsFunc::swapReturnIfNeeded() {
    funcType.swapReturn = funcType.isRvBig && returnExprs.size() == 1;
    if (funcType.swapReturn) {
        funcType.returnParamIndex = funcType.isMethod && !funcType.isStatic;
        funcType.params.insert(funcType.params.begin(), new LgsParam(funcType.rt));
        funcType.rt = &LGS_VOID;
    }
}

Value* LgsFunc::createIRValue(LgsRuntime* runtime) {
    return IRValue;
}

string LgsFunc::prettyName() {
    return funcType.prettyName();
}

string LgsFunc::format(string& tabs) {
    stringstream str;
    str << funcType.name << "(";
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        str << param->format(tabs);
        if (i != funcType.params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType.name != LOGOS_MAIN_FUNC) {
        str << funcType.rt->getIRName();
    }
    str << stmtBlock->format(tabs);
    return str.str();
}

json LgsFunc::asJSON() {
    json tree;
    tree["name"] = funcType.name;
    tree["type"] = funcType.rt->getIRName();
    tree["params"] = {};
    for (const auto& param : funcType.params) {
        tree["params"].emplace_back(param->asJSON());
    }
    tree["stmts"] = stmtBlock->asJSON();
    return tree;
}

LgsFunc::~LgsFunc() {
    if (!funcType.isBuiltin) {
        for (int i = funcType.isMethod; i < funcType.params.size(); ++i) {
            delete funcType.params[i];
        }
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}