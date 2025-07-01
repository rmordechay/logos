#include "exprs/unary/constants/LgsFloatConst.h"


Value* LgsFloatConst::createIRValue(LgsModule* runtime) {
    return ConstantFP::get(runtime->builder.getFloatTy(), value);
}
