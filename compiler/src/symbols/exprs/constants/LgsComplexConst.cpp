#include "symbols/exprs/constants/LgsComplexConst.h"

void LgsComplexConst::setDebugValue(LgsCodeGen& cg) {
}

Value* LgsComplexConst::loadIR(LgsCodeGen& cg) {
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
