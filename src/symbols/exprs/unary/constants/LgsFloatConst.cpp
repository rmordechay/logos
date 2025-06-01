#include "exprs/unary/constants/LgsFloatConst.h"

Value* LgsFloatConst::createIRValue(CodegenMetadata* metadata) {
    return ConstantFP::get(metadata->builder.getFloatTy(), value);
}
