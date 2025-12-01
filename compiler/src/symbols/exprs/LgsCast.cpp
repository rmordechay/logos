#include "exprs/LgsCast.h"
#include "LgsType.h"
#include "LgsUtils.h"

Value* LgsCast::loadIR(LgsCgModule& cg) {
    return value->loadIR(cg);
}

std::string LgsCast::asText() {
    return fromValue->asText() + "->" + toType->pname();
}

void LgsCast::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsCast::~LgsCast() {
    freeExpr(fromValue);
    freeType(toType);
    fromValue = nullptr;
    toType = nullptr;
}
