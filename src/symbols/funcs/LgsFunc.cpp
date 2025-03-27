#include "funcs/LgsFunc.h"

void LgsFunc::setComposedName() {
    if (signature.name == LOGOS_MAIN_FUNC) {
        signature.composedName = signature.name;
        return;
    }
    for (const auto& param : params) {
        signature.argTypeNames.emplace_back(param->type->getName());
    }
    signature.setComposedName();
}

void LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    if (!IRFunc) setIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    metadata->logosStack.exitScope(metadata);
}

json LgsFunc::asJson() {
    json tree;
    tree["name"] = signature.name;
    tree["returnType"] = signature.type->getName();
    for (const auto& param : params) {
        tree["params"].emplace_back(param->asJson());
    }
    tree["stmts"] = stmtBlock->asJson();
    return tree;
}

LgsFunc::~LgsFunc() {
    delete stmtBlock;
}