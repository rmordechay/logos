#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsRuntime* runtime, Value* instance) {
    IRValue = runtime->builder.CreateStructGEP(parent->getIRType(), instance, position);
    return IRValue;
}

void LgsField::storeIRValue(LgsRuntime* runtime, Value* instance, LgsExpr* expr) {
    const auto exprIRValue = expr->getIRValue(runtime);
    runtime->builder.CreateStore(exprIRValue, getGEP(runtime, instance));
}

LgsField* LgsField::clone() const {
    const auto newField = new LgsField(name, type, expr);
    newField->position = position;
    newField->isConst = isConst;
    newField->isPublic = isPublic;
    return newField;
}

json LgsField::asJSON() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->prettyName();
    return tree;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
