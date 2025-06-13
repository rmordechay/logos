#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsRuntime* runtime, Type* parentType, Value* instance) {
    return runtime->builder.CreateStructGEP(parentType, instance, position);
}

void LgsField::storeIRValue(LgsRuntime* runtime, Type* parentType, Value* parentIRValue, LgsExpr* expr) {
    const auto exprIRValue = expr->getIRValue(runtime);
    runtime->builder.CreateStore(exprIRValue, getGEP(runtime, parentType, parentIRValue));
}

LgsField* LgsField::clone() const {
    const auto newField = new LgsField(name, parentName, type, expr);
    newField->position = position;
    newField->isConst = isConst;
    newField->isPublic = isPublic;
    return newField;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
