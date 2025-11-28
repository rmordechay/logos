#include "exprs/constants/LgsCharConst.h"

Value* LgsCharConst::loadIR(LgsCgModule& cg) {
    return IRValue;
}

Value* LgsCharConst::castIR(LgsCgModule& cg, LgsType* toType) {
    assert(0);
}

std::string LgsCharConst::asText() {
    return type->pname();
}
