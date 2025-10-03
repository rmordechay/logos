#include "exprs/LgsCast.h"
#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::loadIR(LgsLLVMGen& cg) {
    return value->loadIR(cg);
}

std::string LgsCast::getName() {
    return fromValue->getName() + "->" + toType->pname();
}

json::value LgsCast::asJsonStr() {
    assert(0);
}

LgsCast::~LgsCast() {
    freeExpr(fromValue);
    freeType(toType);
    fromValue = nullptr;
    toType = nullptr;
}
