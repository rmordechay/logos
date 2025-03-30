#include "funcs/LgsFunc.h"

#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsVoid.h"

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
    setIRFunc(metadata);
    metadata->logosStack.enterScope(this);
    for (const auto& param : params) {
        metadata->logosStack.addLocalSymbol(param->name, param);
    }
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (signature.type->getName() == LgsVoid::name) {
        metadata->builder.CreateRetVoid();
    }
    metadata->logosStack.exitScope(metadata);
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    if (!IRFunc) setIRFunc(metadata);
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