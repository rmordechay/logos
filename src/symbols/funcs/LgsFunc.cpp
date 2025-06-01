#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

void LgsFunc::generateIRCode(CodeGenMetadata* metadata) {
    metadata->runtime.enterScope(this);
    startBlockFunc(metadata);
    IRValue = getIRFunc(metadata);
    stmtBlock->createIRValue(metadata);
    if (funcType.rt->isVoid) {
        metadata->builder.CreateRetVoid();
    }
    metadata->runtime.exitScope();
}

Value* LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    generateIRCode(metadata);
    return IRValue;
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    int iterStart = funcType.isStatic;
    bool isObjReturn = false;
    if (const auto obj = funcType.rt->asObject()) {
        const auto objRtPtr = metadata->builder.CreateAlloca(obj->getIRType(), nullptr);
        IRArgs.push_back(objRtPtr);
        isObjReturn = true;
        iterStart++;
    }
    if (funcType.hasDefaultParams) assert(false);
    if (funcType.isVariadic) {
        auto isInit = false;
        for (int i = iterStart; i < args.size(); ++i) {
            if (!isInit && funcType.params[i]->isVariadic) {
                IRArgs.emplace_back(metadata->builder.getInt32(3));
                isInit = true;
            }
            addIRArg(metadata, IRArgs, args[i]);
        }
    } else {
        for (int i = iterStart; i < args.size(); ++i) {
            addIRArg(metadata, IRArgs, args[i]);
        }
    }
    const auto rv = callIR(metadata, IRArgs);
    if (isObjReturn) return IRArgs[0];
    return rv;
}

void LgsFunc::addIRArg(CodeGenMetadata* metadata, vector<Value*>& IRArgs, LgsExpr* arg) const {
    const auto argIRValue = arg->getIRValue(metadata);
    if (shouldLoadIRArg(argIRValue)) {
        const auto artIRType = arg->type->getIRType();
        const auto value = metadata->builder.CreateLoad(artIRType, argIRValue);
        IRArgs.emplace_back(value);
    } else {
        IRArgs.emplace_back(argIRValue);
    }
}

Value* LgsFunc::callIR(CodeGenMetadata* metadata, const vector<Value*>& args) {
    if (IRValue) {
        const auto IRFuncType = getIRFuncType(metadata);
        return metadata->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(metadata);
    return metadata->builder.CreateCall(IRFunc, args);
}

string LgsFunc::prettyName() {
    return funcType.prettyName();
}

Function* LgsFunc::getIRFunc(CodeGenMetadata* metadata) {
    const auto funcIRType = getIRFuncType(metadata);
    auto func = metadata->module->getOrInsertFunction(funcType.getIRName(), funcIRType);
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    if (const auto obj = funcType.rt->asObject()) {
        AttrBuilder builder(context);
        builder.addStructRetAttr(obj->getIRType());
        args->addAttrs(builder);
        args->setName("rt");
        args++;
    }

    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        if (param->isVariadic) {
            args->setName("argc");
            args++;
        } else {
            param->setIRValue(args);
        }
        if (param->expr) param->expr->setIRValue(args);
        args->setName(param->name);
        args++;
    }
    return IRFunc;
}

FunctionType* LgsFunc::getIRFuncType(const CodeGenMetadata* metadata) {
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

    Type* rt = nullptr;
    if (const auto obj = funcType.rt->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), PointerType::get(obj->getIRType(), 0));
        rt = voidTy;
    } else {
        rt = funcType.rt->getIRType();
    }

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
    // TODO free params
    // for (int i = funcType.isMethod; i < funcType.params.size(); ++i) {
    //     delete funcType.params[i];
    // }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
