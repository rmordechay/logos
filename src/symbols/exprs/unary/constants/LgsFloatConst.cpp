#include "exprs/unary/constants/LgsFloatConst.h"

json::value LgsFloatConst::asJSON() {
    assert(0);
}

std::string LgsFloatConst::pname() {
    return type->pname();
}
