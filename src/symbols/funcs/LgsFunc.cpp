#include "funcs/LgsFunc.h"

#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtBlock.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

void LgsFunc::generateIR(LgsRuntime* runtime) {
    runtime->stack.enterFunc(this);
    startBlockFunc(runtime);
    stmtBlock->createIRValue(runtime);
    if (funcType->rt->isVoid) {
        runtime->freeExprs();
        if (!runtime->builder.GetInsertBlock()->getTerminator()) {
            runtime->builder.CreateRetVoid();
        }
    }
    runtime->stack.exitFunc();
}

Value* LgsFunc::createIRValue(LgsRuntime* runtime) {
    runtime->savedIP = runtime->builder.saveIP();
    generateIR(runtime);
    runtime->builder.restoreIP(runtime->savedIP);
    return getIRFunc(runtime);
}

Function* LgsFunc::getIRFunc(LgsRuntime* runtime) {
    const auto funcIRName = funcType->getIRName();
    auto IRFunc = runtime->module->getFunction(funcIRName);
    if (IRFunc) return IRFunc;
    const auto IRFuncType = funcType->getIRType();
    const auto funcTy = dyn_cast<FunctionType>(IRFuncType);
    auto func = runtime->module->getOrInsertFunction(funcIRName, funcTy);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (funcType->hasFlag(SWAP_RETURN)) {
        setBigObjAttrs(*IRFunc);
    }
    if (funcType->params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (auto& param : funcType->params) {
        param.setIRValue(args);
        args->setName(param.name);
        args++;
    }
    return IRFunc;
}

Value* LgsFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    if (funcType->hasFlag(HAS_DEFAULTS)) assert(0);
    if (funcType->hasFlag(VARIADIC)) assert(0);
    for (int i = funcType->hasFlag(STATIC); i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argType = arg->type->getIRType();
        const auto argValue = arg->getIRValue(runtime);
        const auto IRArg = addIRArg(runtime, argType, argValue);
        IRArgs.push_back(IRArg);
    }
    return callIR(runtime, IRArgs);
}

Value* LgsFunc::callIR(LgsRuntime* runtime, const vector<Value*>& args) {
    if (IRValue) {
        const auto IRFuncType = cast<FunctionType>(funcType->rt->getIRType());
        return runtime->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(runtime);
    if (funcType->hasFlag(SWAP_RETURN)) {
        const auto paramIRType = getReturnSwapParam().type->getIRType();
        const auto rv = runtime->builder.CreateAlloca(paramIRType);
        vector finalArgs(args.begin(), args.end());
        finalArgs.insert(finalArgs.begin() + funcType->returnParamIndex, rv);
        runtime->builder.CreateCall(IRFunc, finalArgs);
        return rv;
    }
    return runtime->builder.CreateCall(IRFunc, args);;
}

Value* LgsFunc::addIRArg(LgsRuntime* runtime, Type* type, Value* value) {
    if (shouldLoadIRArg(value)) {
        return runtime->builder.CreateLoad(type, value);
    }
    return value;
}

void LgsFunc::setBigObjAttrs(Function& IRFunc) const {
    const auto paramIRType = getReturnSwapParam().type->getIRType();
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::StructRet, paramIRType));
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::Writable));
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::NoAlias));
}

bool LgsFunc::shouldLoadIRArg(Value* value) {
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
    if (isa<Function>(value)) return false;
    return true;
}

LgsParam LgsFunc::getReturnSwapParam() const {
    if (!funcType->hasFlag(SWAP_RETURN)) assert(0);
    if (funcType->returnParamIndex > funcType->params.size()) assert(0);
    return funcType->params[funcType->returnParamIndex];
}

void LgsFunc::swapReturnIfNeeded() const {
    bool isEqual = true;
    for (const auto expr1 : returnExprs) {
        for (const auto expr2 : returnExprs) {
            if (expr1 == expr2) continue;
            if (expr1->equals(expr2)) continue;
            isEqual = false;
            break;
        }
    }
    if (funcType->isBig && isEqual) {
        funcType->setFlag(SWAP_RETURN);
        funcType->returnParamIndex = funcType->hasFlag(METHOD) && !funcType->hasFlag(STATIC);
        funcType->params.insert(funcType->params.begin(), LgsParam(funcType->rt));
        funcType->rt = &LGS_VOID;
    }
}

string LgsFunc::prettyName() {
    return funcType->prettyName();
}

string LgsFunc::format(string& tabs) {
    stringstream str;
    str << funcType->name << "(";
    for (int i = 0; i < funcType->params.size(); ++i) {
        auto param = funcType->params[i];
        str << param.format(tabs);
        if (i != funcType->params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType->name != LOGOS_MAIN_FUNC) {
        str << funcType->rt->getIRName();
    }
    str << stmtBlock->format(tabs);
    return str.str();
}

json LgsFunc::asJSON() {
    json tree;
    tree["name"] = funcType->name;
    tree["type"] = funcType->rt->getIRName();
    tree["params"] = {};
    for (auto& param : funcType->params) {
        tree["params"].emplace_back(param.asJSON());
    }
    tree["stmts"] = stmtBlock->asJSON();
    return tree;
}

LgsFunc::~LgsFunc() {
    if (stmtBlock) {
        delete stmtBlock;
    }
}