#include "exprs/unary/constants/LgsFloatConst.h"

Value* LgsFloatConst::createIRValue(Module* module) {
    return ConstantFP::get(builder.getFloatTy(), value);
}
