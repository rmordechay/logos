#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsInstance.h"

Value* LgsField::getGEP(Module* module, Value* instance) {
    assert(instance && parent);
    IRValue = builder.CreateStructGEP(parent->getIRType(), instance, position);
    return IRValue;
}

void LgsField::setFieldIRValue(Module* module, LgsExpr* expr, Value* instance) {
    const auto exprIRValue = expr->getIRValue(module);
    builder.CreateStore(exprIRValue, getGEP(module, instance));
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
