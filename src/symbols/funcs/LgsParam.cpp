#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"

Value* LgsParam::getIRValue(CodeGenMetadata* metadata) {
    if (IRValue) return IRValue;
    return createIRValue(metadata);
}

Value* LgsParam::createIRValue(CodeGenMetadata* metadata) const {
    return nullptr;
}

json LgsParam::asJson() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->getName();
    tree["expr"] = nullptr;
    return tree;
}

LgsParam::~LgsParam() {
    if (expr) {
        delete expr;
    }
}
