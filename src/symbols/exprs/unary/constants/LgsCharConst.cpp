#include "exprs/unary/constants/LgsCharConst.h"


Value* LgsCharConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}

json LgsCharConst::asJson() {
    json tree;
    tree["exprType"] = "CharConst";
    tree["name"] = type->getName();
    tree["value"] = value;
    return tree;
}