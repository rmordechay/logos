#include "funcs/LgsParam.h"
#include "LgsType.h"

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}

LgsParam* LgsParam::clone() {
    const auto cloned = new LgsParam(type, name);
    cloned->location = location;
    if (expr) {
        cloned->expr = expr->clone();
    }
    cloned->isSelf = isSelf;
    cloned->isVariadic = isVariadic;
    return cloned;
}
