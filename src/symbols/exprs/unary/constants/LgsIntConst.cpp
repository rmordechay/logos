#include "constants/LgsIntConst.h"

Value* LgsIntConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt32(value);
}

Value* LgsIntConst::operator+(LgsExpr* other) {
    return LgsConstant::operator+(other);
}
