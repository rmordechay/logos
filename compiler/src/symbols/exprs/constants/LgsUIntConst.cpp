#include "exprs/constants/LgsUIntConst.h"

#include <assert.h>

LgsExpr* LgsUIntConst::cast(LgsType* toType, bool explicitly) {
    if (!toType || !toType->isScalar()) return this;
    if (!inRange(value, toType)) return this;
    setType(toType);
    return this;
}

std::string LgsUIntConst::asText() {
    return std::to_string(value);
}

void LgsUIntConst::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}
