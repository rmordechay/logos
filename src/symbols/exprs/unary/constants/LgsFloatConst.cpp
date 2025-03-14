#include "constants/LgsFloatConst.h"

Value* LgsFloatConst::createIRValue(CodeGenMetadata* metadata) {
    return ConstantFP::get(metadata->builder.getFloatTy(), value);
}

Value* LgsFloatConst::operator+(LgsExpr* other) {
    return LgsConstant::operator+(other);
}
