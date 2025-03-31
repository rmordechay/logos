#include "funcs/LgsFunc.h"

#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsVoid.h"

void LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope(this);
    setIRFuncType();
    for (const auto& param : signature.params) {
        metadata->logosStack.addLocalSymbol(param->name, param);
    }
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (signature.rt->getName() == LgsVoid::name) {
        metadata->builder.CreateRetVoid();
    }
    metadata->logosStack.exitScope(metadata);
}

Function* LgsFunc::getIRFunc(const CodeGenMetadata* metadata) {
    auto func = metadata->currentModule->getOrInsertFunction(signature.composedName, IRFuncType);
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    if (signature.params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (const auto& param : signature.params) {
        param->setIRValue(args);
        args++->setName(param->name);
    }
    return IRFunc;
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto IRFunc = getIRFunc(metadata);
    vector<Value*> argValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(IRFunc, argValues);
}

json LgsFunc::asJson() {
    json tree;
    tree["name"] = signature.name;
    tree["returnType"] = signature.rtName;
    for (const auto& param : signature.params) {
        tree["params"].emplace_back(param->asJson());
    }
    tree["stmts"] = stmtBlock->asJson();
    return tree;
}

LgsFunc::~LgsFunc() {
    delete stmtBlock;
}