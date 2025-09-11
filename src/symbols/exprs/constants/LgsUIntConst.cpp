#include "exprs/constants/LgsUIntConst.h"

#include "exprs/constants/LgsStrConst.h"

std::string LgsUIntConst::pname() {
    return std::to_string(value);
}

json::value LgsUIntConst::asJSON() {
    assert(0);
}