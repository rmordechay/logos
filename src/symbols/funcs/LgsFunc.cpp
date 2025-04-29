#include "funcs/LgsFunc.h"
#include "LgsData.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

void LgsFunc::generateIRCode(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope(this);
    getIRFunc(metadata);
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (signature.type->getName() == LgsVoid::name) {
        metadata->builder.CreateRetVoid();
    }
    metadata->lgsStack.exitScope();
}

Function* LgsFunc::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) setIRFuncType(metadata);
    if (signature.IRName.empty()) signature.setIRName();
    auto func = metadata->module->getOrInsertFunction(signature.IRName, IRFuncType);
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    if (const auto obj = signature.type->asObject()) {
        setSRet(args, obj);
    }
    if (args) {
        setIRFuncParams(args);
    }
    return IRFunc;
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto IRFunc = getIRFunc(metadata);
    vector<Value*> argValues;
    Value* objPtr = nullptr;
    if (const auto obj = signature.type->asObject()) {
        objPtr = metadata->builder.CreateAlloca(obj->getIRType(), nullptr);;
        argValues.push_back(objPtr);
    }
    for (int i = 0; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    const auto funcCall = metadata->builder.CreateCall(IRFuncType, IRFunc, argValues);
    if (objPtr) {
        return objPtr;
    }
    return funcCall;
}


string LgsFunc::format(string& indentStr) {
    stringstream str;
    str << signature.name << "(";
    for (int i = 0; i < signature.params.size(); ++i) {
        auto param = signature.params[i];
        str << param.format(indentStr);
        if (i != signature.params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (signature.name != LOGOS_MAIN_FUNC) {
        str << signature.type->getName();
    }
    str << stmtBlock->format(indentStr);
    return str.str();
}

void LgsFunc::setSRet(Function::arg_iterator& args, LgsObject* const obj) const {
    AttrBuilder builder(context);
    builder.addStructRetAttr(obj->getIRType());
    args->addAttrs(builder);
    args->setName("rt");
    args++;
}

json LgsFunc::asJSON() {
    json tree;
    tree["name"] = signature.name;
    tree["type"] = signature.type->getName();
    tree["params"] = {};
    for (auto& param : signature.params) {
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
