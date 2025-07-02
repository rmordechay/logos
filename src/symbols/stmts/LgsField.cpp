#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsModule* module, Type* parentType, Value* instance) const {
    return module->builder.CreateStructGEP(parentType, instance, position);
}

void LgsField::storeIRValue(LgsModule* module, Type* parentType, Value* parentIRValue, LgsExpr* expr) const {
    const auto exprIRValue = expr->getIRValue(module);
    module->builder.CreateStore(exprIRValue, getGEP(module, parentType, parentIRValue));
}

void LgsField::setZeroValue(LgsModule* module, Type* parentType, Value* parentIRValue) const {
    if (type->asObject() || type->asArray() || type->asMap()) return;
    const auto exprIRValue = type->getZeroValue()->getIRValue(module);
    module->builder.CreateStore(exprIRValue, getGEP(module, parentType, parentIRValue));
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
