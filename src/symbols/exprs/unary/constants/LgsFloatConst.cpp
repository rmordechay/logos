#include "exprs/unary/constants/LgsFloatConst.h"

Value* LgsFloatConst::createIRValue(CodeGenMetadata* metadata) {
    Constant* const constant = ConstantFP::get(metadata->builder.getFloatTy(), value);
    return constant;
}
