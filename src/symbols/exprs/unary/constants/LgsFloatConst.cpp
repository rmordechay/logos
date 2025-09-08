#include "exprs/unary/constants/LgsFloatConst.h"

Value* LgsFloatConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

json::value LgsFloatConst::asJSON() {
    assert(0);
}

std::string LgsFloatConst::pname() {
    return type->pname();
}
