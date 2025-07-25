#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsModule* module, Type* parentIRType, Value* instance) const {
    return module->builder.CreateStructGEP(parentIRType, instance, position);
}

void LgsField::storeIRValue(LgsModule* module, Type* parentIRType, Value* parentIRValue, LgsExpr* value) const {
    const auto exprIRValue = value->getIRValue(module);
    module->builder.CreateStore(exprIRValue, getGEP(module, parentIRType, parentIRValue));
}

void LgsField::setZeroValue(LgsModule* module, Type* parentType, Value* parentIRValue) const {
    if (type->asObject() || type->asDArray() || type->asMap()) return;
    const auto exprIRValue = type->getZeroValue()->getIRValue(module);
    module->builder.CreateStore(exprIRValue, getGEP(module, parentType, parentIRValue));
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
