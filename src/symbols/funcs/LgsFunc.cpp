#include "funcs/LgsFunc.h"

#include "funcs/LgsParam.h"
#include "types/LgsVoid.h"

void LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope(this);
    const auto IRFunc = getIRFunc(metadata);
    auto args = IRFunc->arg_begin();
    for (const auto& param : signature.params) {
        metadata->logosStack.addLocalSymbol(param->name, param);
        param->setIRValue(args);
        args++->setName(param->name);
    }
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (signature.type->getName() == LgsVoid::name) {
        metadata->builder.CreateRetVoid();
    }
    metadata->logosStack.exitScope(metadata);
}

Function* LgsFunc::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) setIRFuncType();
    string name;
    if (signature.isStatic) {
        name = signature.name;
    } else {
        name = signature.composedName;
    }
    auto func = metadata->currentModule->getOrInsertFunction(name, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
}

json LgsFunc::asJson() {
    json tree;
    tree["name"] = signature.name;
    tree["returnType"] = signature.type->getName();
    for (const auto& param : signature.params) {
        tree["params"].emplace_back(param->asJson());
    }
    tree["stmts"] = stmtBlock->asJson();
    return tree;
}

LgsFunc::~LgsFunc() {
    if (stmtBlock) {
        delete stmtBlock;
    }
}