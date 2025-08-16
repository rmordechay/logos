#include "exprs/unary/constants/LgsFloatConst.h"

void LgsFloatConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = ConstantFP::get(codeGen->builder.getFloatTy(), value);
}

std::string LgsFloatConst::pname() {
    return type->pname();
}
