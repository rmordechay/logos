#include "exprs/unary/constants/LgsFloatConst.h"

json::value_ref LgsFloatConst::asJSON() {
    json::object obj;
    return obj;
}

void LgsFloatConst::createIRValue(LgsCodeGen* codeGen) {
    if (type->asFloat()) {
        IRValue = codeGen->floatv(value);
    } else if (type->asDouble()) {
        IRValue = codeGen->doublev(value);
    } else {
        assert(0);
    }
}

std::string LgsFloatConst::pname() {
    return type->pname();
}
