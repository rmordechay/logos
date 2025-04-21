#include "exprs/unary/constants/LgsBoolConst.h"

Value* LgsBoolConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}