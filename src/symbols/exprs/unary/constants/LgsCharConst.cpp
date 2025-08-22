#include "exprs/unary/constants/LgsCharConst.h"


#include "utils/LgsUtils.h"

std::string LgsCharConst::pname() {
    return type->pname();
}

void LgsCharConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i8(value);
}

json::value LgsCharConst::asJSON() {
    assert(0);
}
