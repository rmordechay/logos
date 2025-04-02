#include "funcs/LgsFunc.h"

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
    if (!IRFuncType) setIRFuncType();
    auto func = metadata->currentModule->getOrInsertFunction(signature.composedName, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
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