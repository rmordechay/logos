#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(CodeGenMetadata* metadata, Value* instance) {
    assert(instance);
    IRValue = metadata->builder.CreateStructGEP(parent->getIRType(), instance, position);
    return IRValue;
}

void LgsField::setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr, Value* instance) {
    const auto exprIRValue = expr->getIRValue(metadata);
    metadata->builder.CreateStore(exprIRValue, getGEP(metadata, instance));
}

LgsField* LgsField::clone() const {
    return new LgsField(*this);
}

json LgsField::asJSON() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->getPrettyName();
    tree["parent"] = parent->name;
    return tree;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
