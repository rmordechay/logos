#include "stmts/LgsVarDec.h"
#include "exprs/unary/constants/LgsConst.h"
#include <LgsStack.h>
#include <json/json.hpp>

Value* LgsVarDec::createIRValue(CodeGenMetadata* metadata) {
    if (!expr) return nullptr;
    Value* exprValue = expr->getIRValue(metadata);
    const auto valueType = exprValue->getType();
    if (!valueType->isPointerTy()) {
        auto& builder = metadata->builder;
        const auto allocaInst = builder.CreateAlloca(valueType);
        builder.CreateStore(exprValue, allocaInst);
    }
    metadata->logosStack.addLocalSymbol(name, this);
    return exprValue;
}

json LgsVarDec::asJson() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->getName();
    tree["expr"] = expr->asJson();
    return tree;
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}

