#include "exprs/unary/constants/LgsFloatConst.h"


Value* LgsFloatConst::createIRValue(LgsCodeGen* codeGen) {
    return ConstantFP::get(codeGen->builder.getFloatTy(), value);
}

string LgsFloatConst::prettyName() {
    return type->prettyName();
}
