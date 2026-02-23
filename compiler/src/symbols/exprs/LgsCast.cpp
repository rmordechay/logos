#include "exprs/LgsCast.h"

#include <assert.h>

#include "LgsType.h"

std::string LgsCast::asText() {
    return fromValue->asText() + "->" + toType->pname();
}

void LgsCast::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsCast::~LgsCast() {
    freeExpr(fromValue);
    freeType(toType);
    fromValue = nullptr;
    toType = nullptr;
}
