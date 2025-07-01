#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsModule* runtime, Type* parentType, Value* instance) const {
    return runtime->builder.CreateStructGEP(parentType, instance, position);
}

void LgsField::storeIRValue(LgsModule* runtime, Type* parentType, Value* parentIRValue, LgsExpr* expr) const {
    const auto exprIRValue = expr->getIRValue(runtime);
    runtime->builder.CreateStore(exprIRValue, getGEP(runtime, parentType, parentIRValue));
}

void LgsField::setZeroValue(LgsModule* runtime, Type* parentType, Value* parentIRValue) const {
    if (type->asObject() || type->asArray() || type->asMap()) return;
    const auto exprIRValue = type->getZeroValue()->getIRValue(runtime);
    runtime->builder.CreateStore(exprIRValue, getGEP(runtime, parentType, parentIRValue));
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
