#include "exprs/unary/constants/LgsFloatConst.h"


Value* LgsFloatConst::createIRValue(LgsModule* module) {
    return ConstantFP::get(module->builder.getFloatTy(), value);
}

string LgsFloatConst::prettyName() {
    return type->prettyName();
}
