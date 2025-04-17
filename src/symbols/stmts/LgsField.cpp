#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getIRValue(CodeGenMetadata* metadata) {
    if (IRValue) return IRValue;
    IRValue = getGEP(metadata);
    return IRValue;
}

void LgsField::setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr) const {
    const auto exprIRValue = expr->getIRValue(metadata);
    metadata->builder.CreateStore(exprIRValue, getGEP(metadata));
}

Value* LgsField::getGEP(CodeGenMetadata* metadata) const {
    assert(parent);
    // return metadata->builder.CreateStructGEP(parentIRType, parentIRValue, position);
    return nullptr;
}
