#include "exprs/unary/constants/LgsCharConst.h"


#include "utils/LgsUtils.h"

std::string LgsCharConst::pname() {
    return type->pname();
}

json::value LgsCharConst::asJSON() {
    assert(0);
}
