#include "symbols/exprs/constants/LgsComplexConst.h"

void LgsComplexConst::setDebugValue(LgsCgModule& cg) {
}

Value* LgsComplexConst::loadIR(LgsCgModule& cg) {
    return LgsExpr::loadIR(cg);
}

std::string LgsComplexConst::asText() {
    assert(0);
}

LgsComplexConst::~LgsComplexConst() {
    freeExpr(real);
    freeExpr(imaginary);
    real = nullptr;
    imaginary = nullptr;
}
