#include "exprs/unary/constants/LgsFloatConst.h"


Value* LgsFloatConst::createIRValue(LgsCodeGen* codeGen) {
    return ConstantFP::get(codeGen->builder.getFloatTy(), value);
}

std::string LgsFloatConst::prettyName() {
    return type->prettyName();
}
