#include "exprs/constants/LgsFloatConst.h"
#include "codegen/LgsCodeGen.h"

std::string LgsFloatConst::asText() {
    return std::to_string(value);
}

void LgsFloatConst::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsFloatConst::clone() {
    return new LgsFloatConst(*this);
}
