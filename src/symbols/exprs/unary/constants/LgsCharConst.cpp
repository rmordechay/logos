#include "exprs/unary/constants/LgsCharConst.h"


#include "utils/LgsUtils.h"


std::string LgsCharConst::pname() {
    return type->pname();
}

json::object LgsCharConst::asJSON() {
    json::object obj;
    return obj;
}

void LgsCharConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i8(value);
}
