#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(LgsRuntime* runtime, Value* instance) {
    assert(instance && parent);
    IRValue = runtime->builder.CreateStructGEP(parent->getIRType(runtime), instance, position);
    return IRValue;
}

void LgsField::setFieldIRValue(LgsRuntime* runtime, LgsExpr* expr, Value* instance) {
    const auto exprIRValue = expr->getIRValue(runtime);
    runtime->builder.CreateStore(exprIRValue, getGEP(runtime, instance));
}

LgsField* LgsField::clone() const {
    return new LgsField(*this);
}

json LgsField::asJSON() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->prettyName();
    tree["parent"] = parent->name;
    return tree;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
