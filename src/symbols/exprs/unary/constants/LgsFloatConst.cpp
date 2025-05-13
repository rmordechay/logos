#include "exprs/unary/constants/LgsFloatConst.h"

Value* LgsFloatConst::createIRValue(CodeGenMetadata* metadata) {
    return ConstantFP::get(metadata->builder.getFloatTy(), value);
}
