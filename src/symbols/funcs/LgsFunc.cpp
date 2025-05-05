#include "funcs/LgsFunc.h"
#include "LgsData.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

void LgsFunc::generateIRCode(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope(this);
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (getFuncType()->rt->getPrettyName() == LgsVoid::name) {
        metadata->builder.CreateRetVoid();
    }
    metadata->lgsStack.exitScope();
}

Value* LgsFunc::setIRArgs(CodeGenMetadata* metadata, vector<Value*>& argValues, const vector<LgsExpr*>& args) {
    Value* objRtPtr = nullptr;
    const auto funcType = getFuncType();
    if (const auto obj = funcType->rt->asObject()) {
        objRtPtr = metadata->builder.CreateAlloca(obj->getIRType(), nullptr);
        argValues.push_back(objRtPtr);
    }
    auto iterSize = 0;
    if (const auto method = dynamic_cast<LgsMethodImpl*>(this)) {
        iterSize = method->isStatic;
    }
    for (int i = iterSize; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    if (objRtPtr) return objRtPtr;
    return nullptr;
}

Function* LgsFunc::getIRFunc(const CodeGenMetadata* metadata) {
    const auto funcType = getFuncType();
    auto func = metadata->module->getOrInsertFunction(funcType->getIRName(), getIRFuncType(metadata));
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    if (const auto obj = funcType->rt->asObject()) {
        setStructRet(args, obj);
    }
    setIRFuncParams(args);
    return IRFunc;
}

void LgsFunc::setStructRet(Function::arg_iterator& args, LgsObject* const obj) const {
    AttrBuilder builder(context);
    builder.addStructRetAttr(obj->getIRType());
    args->addAttrs(builder);
    args->setName("rt");
    args++;
}

FunctionType* LgsFunc::getIRFuncType(const CodeGenMetadata* metadata) {
    if (IRFuncType) return IRFuncType;
    const auto funcType = getFuncType();
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType->params.size(); ++i) {
        auto paramIRType = funcType->params[i]->type->getIRType();
        // TODO make generic
        if (dynamic_cast<LgsInterface*>(funcType->params[i]->type)) {
            paramIRType = paramIRType->getPointerTo();
        }
        IRParamsTypes.emplace_back(paramIRType);
    }
    if (const auto obj = funcType->rt->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), obj->getIRType()->getPointerTo());
        IRFuncType = FunctionType::get(voidTy, IRParamsTypes, false);
    } else {
        IRFuncType = FunctionType::get(funcType->rt->getIRType(), IRParamsTypes, false);
    }
    return IRFuncType;
}


void LgsFunc::setIRFuncParams(Argument* IRParams) {
    for (auto& param : getFuncType()->params) {
        param->setIRValue(IRParams);
        if (param->expr) param->expr->setIRValue(IRParams);
        IRParams->setName(param->getIRName());
        IRParams++;
    }
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args, Value* callback) {
    vector<Value*> argValues;
    const auto objRtPtr = setIRArgs(metadata, argValues, args);
    const auto IRFuncType = getIRFuncType(metadata);
    const auto IRFunc = callback ? callback : getIRFunc(metadata);
    const auto funcCall = metadata->builder.CreateCall(IRFuncType, IRFunc, argValues);
    if (objRtPtr) return objRtPtr;
    return funcCall;
}

string LgsFunc::format(string& indentStr) {
    stringstream str;
    const auto funcType = getFuncType();
    str << funcType->name << "(";
    for (int i = 0; i < funcType->params.size(); ++i) {
        auto param = funcType->params[i];
        str << param->format(indentStr);
        if (i != funcType->params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType->name != LOGOS_MAIN_FUNC) {
        str << funcType->rt->getPrettyName();
    }
    str << stmtBlock->format(indentStr);
    return str.str();
}

json LgsFunc::asJSON() {
    json tree;
    const auto funcType = getFuncType();
    tree["name"] = funcType->name;
    tree["type"] = funcType->rt->getPrettyName();
    tree["params"] = {};
    for (auto& param : funcType->params) {
        tree["params"].emplace_back(param->asJSON());
    }
    tree["stmts"] = stmtBlock->asJSON();
    return tree;
}


LgsFunc::~LgsFunc() {
    if (stmtBlock) {
        delete stmtBlock;
    }
}
