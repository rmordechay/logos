#include "exprs/constants/LgsCharConst.h"

Value* LgsCharConst::loadIR(LgsCgModule& cg) {
    return IRValue;
}

std::string LgsCharConst::asText() {
    return type->pname();
}
