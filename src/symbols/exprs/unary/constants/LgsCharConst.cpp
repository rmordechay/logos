#include "exprs/unary/constants/LgsCharConst.h"


#include "utils/LgsUtils.h"


std::string LgsCharConst::pname() {
    return type->pname();
}

json::value_ref LgsCharConst::asJSON() {
    json::object obj;
    return obj;
}

void LgsCharConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i8(value);
}
