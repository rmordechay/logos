#include "exprs/unary/constants/LgsBoolConst.h"

Value* LgsBoolConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}

json LgsBoolConst::asJson() {
    json tree;
    tree["name"] = type->getName();
    tree["value"] = value;
    return tree;
}