#include "exprs/LgsCast.h"
#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::loadIR(LgsLLVMGen& cg) {
    return value->loadIR(cg);
}

std::string LgsCast::asText() {
    return fromValue->asText() + "->" + toType->pname();
}

LgsCast::~LgsCast() {
    freeExpr(fromValue);
    freeType(toType);
    fromValue = nullptr;
    toType = nullptr;
}
