#include "exprs/constants/LgsUIntConst.h"

std::string LgsUIntConst::asText() {
    return std::to_string(value);
}

void LgsUIntConst::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}
