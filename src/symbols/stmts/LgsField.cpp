#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(CodeGenMetadata* metadata, Value* instance) {
    if (IRValue) return IRValue;
    assert(instance);
    IRValue = metadata->builder.CreateStructGEP(parent->getIRType(), instance, position, parent->name + "_" + name + "_gep");
    return IRValue;
}

void LgsField::setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr, Value* instance) {
    const auto exprIRValue = expr->getIRValue(metadata);
    metadata->builder.CreateStore(exprIRValue, getGEP(metadata, instance));
}

json LgsField::asJSON() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->getName();
    tree["parent"] = parent->name;
    return tree;
}

LgsField::~LgsField() {
    delete userType;
    if (expr) delete expr;
}
