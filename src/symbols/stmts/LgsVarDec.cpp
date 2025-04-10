#include "stmts/LgsVarDec.h"

#include "exprs/unary/LgsArray.h"

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
    IRValue = exprValue;
    return exprValue;
}

void LgsVarDec::free(CodeGenMetadata* metadata) {
    expr->free(metadata);
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}

