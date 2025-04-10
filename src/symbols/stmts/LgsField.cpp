#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"

void LgsField::setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr) {
    const auto exprIRValue = expr->getIRValue(metadata);
    metadata->builder.CreateStore(exprIRValue, getGEP(metadata));
}

Value* LgsField::getIRValue(CodeGenMetadata* metadata) {
    if (!IRValue) IRValue = createIRValue(metadata);
    assert(IRValue);
    return IRValue;
}

Value* LgsField::createIRValue(CodeGenMetadata* metadata) {
    if (expr) {
        return expr->getIRValue(metadata);
    }
    return metadata->builder.CreateLoad(type->getIRType(), getGEP(metadata));
}

Value* LgsField::getGEP(CodeGenMetadata* metadata) {
    if (gep) return gep;
    const auto parentTy = parentExpr->type->getIRType();
    const auto self = parentExpr->getIRValue(metadata);
    gep = metadata->builder.CreateStructGEP(parentTy, self, position);
    return gep;
}
