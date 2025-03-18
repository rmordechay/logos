#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"

Value* LgsParam::createIRValue(CodeGenMetadata* metadata) {
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
