#include "constants/LgsBoolConst.h"

Value* LgsBoolConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}

Value* LgsBoolConst::operator+(LgsExpr* other) {
    return LgsConstant::operator+(other);
}
