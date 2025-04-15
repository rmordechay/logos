#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "types/LgsObject.h"

Value* LgsField::getIRValue(CodeGenMetadata* metadata) {
    if (!IRValue) IRValue = createIRValue(metadata);
    return IRValue;
}

Value* LgsField::createIRValue(CodeGenMetadata* metadata) {
    if (expr) return expr->getIRValue(metadata);
    const auto gep = getGEP(metadata);
    return metadata->builder.CreateLoad(type->getIRType(), gep);
}

void LgsField::setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr) const {
    const auto exprIRValue = expr->getIRValue(metadata);
    const auto gep = getGEP(metadata);
    metadata->builder.CreateStore(exprIRValue, gep);
}

Value* LgsField::getGEP(CodeGenMetadata* metadata) const {
    assert(parentIRValue);
    assert(parentIRType);
    return metadata->builder.CreateStructGEP(parentIRType, parentIRValue, position);
}
