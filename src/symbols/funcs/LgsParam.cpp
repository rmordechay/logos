#include "funcs/LgsParam.h"
#include "LgsType.h"

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsParam::asText() {
    return name;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}

LgsParam* LgsParam::clone() const {
    const auto cloned = new LgsParam(type, name);
    cloned->location = location;
    if (expr) {
        cloned->expr = expr->cloneExpr();
    }
    cloned->isSelf = isSelf;
    cloned->isVariadic = isVariadic;
    return cloned;
}
