#include "exprs/unary/constants/LgsTypeConst.h"

#include "AntlrConverter.h"

string LgsTypeConst::getName() {
    return type->getName();
}

Value* LgsTypeConst::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

json LgsTypeConst::asJson() {
    json tree;
    tree["exprType"] = "TypeConst";
    tree["name"] = type->getName();
    tree["value"] = type->getName();
    return tree;
}