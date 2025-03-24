#include "stmts/LgsVarDec.h"
#include "exprs/unary/constants/LgsConst.h"
#include <LgsStack.h>
#include <json/json.hpp>

Value* LgsVarDec::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    if (!expr) return builder.CreateAlloca(type->getIRType());

    const auto exprValue = expr->getIRValue(metadata);
    const auto valueType = exprValue->getType();
    // Pointers don't need to be stored
    if (!valueType->isPointerTy()) {
        const auto ptr = builder.CreateAlloca(valueType);
        builder.CreateStore(exprValue, ptr);
    }
    metadata->logosStack.addLocalSymbol(name, this);
    IRValue = exprValue;
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

