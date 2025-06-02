#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"

#include "stmts/LgsStmtBlock.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

void LgsFunc::generateIRCode(Module* module) {
    runtime.stack.enterFunc(this);
    startBlockFunc(module);
    const auto IRFunc = getIRFunc(module);
    IRValue = IRFunc;
    stmtBlock->createIRValue(module);
    if (funcType.rt->isVoid) {
        runtime.freeExprs(module);
        builder.CreateRetVoid();
    }
    runtime.stack.exitFunc();
}

Value* LgsFunc::createIRValue(Module* module) {
    return IRValue;
}

Value* LgsFunc::call(Module* module, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    const int iterStart = funcType.isStatic;
    if (funcType.hasDefaultParams) assert(false);
    if (funcType.isVariadic) {
        auto isInit = false;
        for (int i = iterStart; i < args.size(); ++i) {
            if (!isInit && funcType.params[i]->isVariadic) {
                IRArgs.emplace_back(builder.getInt32(3));
                isInit = true;
            }
            addIRArg(module, IRArgs, args[i]);
        }
    } else {
        for (int i = iterStart; i < args.size(); ++i) {
            addIRArg(module, IRArgs, args[i]);
        }
    }
    return callIR(module, IRArgs);
}

void LgsFunc::addIRArg(Module* module, vector<Value*>& IRArgs, LgsExpr* arg) const {
    const auto argIRValue = arg->getIRValue(module);
    if (shouldLoadIRArg(argIRValue)) {
        const auto artIRType = arg->type->getIRType();
        const auto value = builder.CreateLoad(artIRType, argIRValue);
        IRArgs.emplace_back(value);
    } else {
        IRArgs.emplace_back(argIRValue);
    }
}

Value* LgsFunc::callIR(Module* module, const vector<Value*>& args) {
    if (IRValue) {
        const auto IRFuncType = getIRFuncType(module);
        return builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(module);
    return builder.CreateCall(IRFunc, args);
}

string LgsFunc::prettyName() {
    return funcType.prettyName();
}

Function* LgsFunc::getIRFunc(Module* module) {
    const auto funcIRType = getIRFuncType(module);
    auto func = module->getOrInsertFunction(funcType.getIRName(), funcIRType);
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

FunctionType* LgsFunc::getIRFuncType(const Module* module) {
    if (IRFuncType) return IRFuncType;
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        const auto paramType = param->type;
        auto paramIRType = paramType->getIRType();
        if (!paramType->isPrimitive) {
            paramIRType = ptrTy;
        }
        if (param->isVariadic) {
            IRParamsTypes.emplace_back(i32Ty);
        }
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto rt = funcType.rt->getIRType();
    IRFuncType = FunctionType::get(rt, IRParamsTypes, funcType.isVariadic);
    return IRFuncType;
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
