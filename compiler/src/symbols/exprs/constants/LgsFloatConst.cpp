#include "exprs/constants/LgsFloatConst.h"

#include <assert.h>

std::string LgsFloatConst::asText() {
    return std::to_string(value);
}

void LgsFloatConst::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsFloatConst::clone() const {
    return new LgsFloatConst(*this);
}
