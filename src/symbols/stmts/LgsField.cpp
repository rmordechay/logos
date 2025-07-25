#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsModule* module) const {
    return module->builder.CreateStructGEP(parentIRType, parentIRValue, position);
}

void LgsField::storeIRValue(LgsModule* module, LgsExpr* value) const {
    const auto exprIRValue = value->getIRValue(module);
    module->builder.CreateStore(exprIRValue, getGEP(module));
}

void LgsField::setZeroValue(LgsModule* module) const {
    if (type->asObject() || type->asDArray() || type->asMap()) return;
    const auto exprIRValue = type->getZeroValue()->getIRValue(module);
    module->builder.CreateStore(exprIRValue, getGEP(module));
}

LgsField* LgsField::clone() const {
    const auto cloned = new LgsField(name, parentName, type, expr);
    cloned->position = position;
    cloned->isPublic = isPublic;
    cloned->isVirtual = isVirtual;
    cloned->isOptional = isOptional;
    return cloned;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
