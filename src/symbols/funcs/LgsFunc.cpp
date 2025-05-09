#include "funcs/LgsFunc.h"
#include "LgsDefinitions.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

void LgsFunc::generateIRCode(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope(this);
    startBlock(metadata, entryBlock);
    createIRFunc(metadata);
    stmtBlock->createIRValue(metadata);
    if (getFuncType()->rt->isVoidType) {
        metadata->builder.CreateRetVoid();
    }
    metadata->lgsStack.exitScope();
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args, Value* callback) {
    vector<Value*> argValues;
    const auto isObjReturn = setIRArgs(metadata, argValues, args);
    const auto IRFuncType = getIRFuncType(metadata);
    const auto IRFunc = callback ? callback : createIRFunc(metadata);
    const auto funcCall = metadata->builder.CreateCall(IRFuncType, IRFunc, argValues);
    if (isObjReturn) return argValues[0];
    return funcCall;
}

Value* LgsFunc::makeCall(CodeGenMetadata* metadata, const vector<Value*>& args) {
    const auto IRFuncType = getIRFuncType(metadata);
    const auto IRFunc = createIRFunc(metadata);
    return metadata->builder.CreateCall(IRFuncType, IRFunc, args);
}

Function* LgsFunc::createIRFunc(const CodeGenMetadata* metadata) {
    const auto funcType = getFuncType();
    const auto funcIRType = getIRFuncType(metadata);
    auto func = metadata->module->getOrInsertFunction(funcType->getIRName(), funcIRType);
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    if (const auto obj = funcType->rt->asObject()) {
        setStructRet(args, obj);
    }
    setIRParams(IRFunc, args);
    return IRFunc;
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

    Type* rt = nullptr;
    if (const auto obj = funcType->rt->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), obj->getIRType()->getPointerTo());
        rt = voidTy;
    } else {
        rt = funcType->rt->getIRType();
    }
    IRFuncType = FunctionType::get(rt, IRParamsTypes, false);
    return IRFuncType;
}

bool LgsFunc::setIRArgs(CodeGenMetadata* metadata, vector<Value*>& argValues, const vector<LgsExpr*>& args) {
    const auto funcType = getFuncType();
    bool isObjReturn = false;
    if (const auto obj = funcType->rt->asObject()) {
        const auto objRtPtr = metadata->builder.CreateAlloca(obj->getIRType(), nullptr);
        argValues.push_back(objRtPtr);
        isObjReturn = true;
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
    return isObjReturn;
}

void LgsFunc::setIRParams(Function* func, Argument* IRParams) {
    const auto params = getFuncType()->params;
    for (int i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        param->setIRValue(IRParams);
        if (param->expr) param->expr->setIRValue(IRParams);
        func->addParamAttr(0, Attribute::NoUndef);
        IRParams->setName(param->getIRName());
        IRParams++;
    }
}

void LgsFunc::setStructRet(Function::arg_iterator& args, LgsObject* const obj) const {
    AttrBuilder builder(context);
    builder.addStructRetAttr(obj->getIRType());
    args->addAttrs(builder);
    args->setName("rt");
    args++;
}

string LgsFunc::format(string& indentStr) {
    stringstream str;
    const auto funcType = getFuncType();
    str << funcType->name << "(";
    for (int i = 0; i < funcType->params.size(); ++i) {
        const auto param = funcType->params[i];
        str << param->format(indentStr);
        if (i != funcType->params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType->name != LOGOS_MAIN_FUNC) {
        str << funcType->rt->getIRName();
    }
    str << stmtBlock->format(indentStr);
    return str.str();
}

json LgsFunc::asJSON() {
    json tree;
    const auto funcType = getFuncType();
    tree["name"] = funcType->name;
    tree["type"] = funcType->rt->getIRName();
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
