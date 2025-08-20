#include "exprs/unary/constants/LgsFloatConst.h"

void LgsFloatConst::createIRValue(LgsCodeGen* codeGen) {
    if (type->asFloat()) {
        IRValue = codeGen->floatv(value);
    } else if (type->asDouble()) {
        IRValue = codeGen->doublev(value);
    } else {
        assert(0);
    }
}

json::value LgsFloatConst::asJSON() {
    assert(0);
}

std::string LgsFloatConst::pname() {
    return type->pname();
}
