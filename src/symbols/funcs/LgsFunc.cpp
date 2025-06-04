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
    const auto IRFunc = getIRFunc(runtime);
    IRValue = IRFunc;
    stmtBlock->createIRValue(runtime);
    if (funcType.rt->isVoid) {
        runtime->freeExprs(runtime);
        runtime->builder.CreateRetVoid();
    }
    runtime->stack.exitFunc();
}

Value* LgsFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    const int iterStart = funcType.isStatic;
    if (funcType.hasDefaultParams) assert(false);
    if (funcType.isVariadic) {
        auto isInit = false;
        for (int i = iterStart; i < args.size(); ++i) {
            if (!isInit && funcType.params[i]->isVariadic) {
                IRArgs.emplace_back(runtime->builder.getInt32(3));
                isInit = true;
            }
            addIRArg(runtime, IRArgs, args[i]);
        }
    } else {
        for (int i = iterStart; i < args.size(); ++i) {
            addIRArg(runtime, IRArgs, args[i]);
        }
    }
    return callIR(runtime, IRArgs);
}

Value* LgsFunc::callIR(LgsRuntime* runtime, const vector<Value*>& args) {
    if (IRValue) {
        const auto IRFuncType = getIRFuncType(runtime);
        return runtime->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(runtime);
    return runtime->builder.CreateCall(IRFunc, args);
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

Value* LgsFunc::createIRValue(LgsRuntime* runtime) {
    return IRValue;
}

string LgsFunc::prettyName() {
    return funcType.prettyName();
}

Function* LgsFunc::getIRFunc(LgsRuntime* runtime) {
    const auto f = runtime->module->getFunction(funcType.getIRName());
    if (f) return f;
    const auto funcIRType = getIRFuncType(runtime);
    auto func = runtime->module->getOrInsertFunction(funcType.getIRName(), funcIRType);
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        if (param->isVariadic) {
            args++->setName("argc");
        } else {
            param->setIRValue(args);
        }
        if (param->expr) param->expr->setIRValue(args);
        args->setName(param->name);
        args++;
    }
    return IRFunc;
}

FunctionType* LgsFunc::getIRFuncType(LgsRuntime* runtime) {
    if (IRFuncType) return IRFuncType;
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        const auto paramType = param->type;
        auto paramIRType = paramType->getIRType();
        if (!paramType->isPrimitive) {
            paramIRType = PointerType::getUnqual(context);
        }
        if (param->isVariadic) {
            IRParamsTypes.emplace_back(runtime->builder.getInt32Ty());
        }
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto rt = funcType.rt->getIRType();
    IRFuncType = FunctionType::get(rt, IRParamsTypes, funcType.isVariadic);
    return IRFuncType;
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
