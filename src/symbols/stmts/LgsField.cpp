#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsRuntime* runtime, Value* instance) {
    return runtime->builder.CreateStructGEP(parent->getIRType(), instance, position);
}

void LgsField::storeIRValue(LgsRuntime* runtime, Value* parentIRValue, LgsExpr* expr) {
    const auto exprIRValue = expr->getIRValue(runtime);
    runtime->builder.CreateStore(exprIRValue, getGEP(runtime, parentIRValue));
}

LgsField* LgsField::clone() const {
    const auto newField = new LgsField(name, type, expr);
    newField->position = position;
    newField->isConst = isConst;
    newField->isPublic = isPublic;
    return newField;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
