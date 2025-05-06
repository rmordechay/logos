#include "exprs/unary/constants/LgsLongConst.h"

Value* LgsLongConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt64(value);
}

LgsExpr* LgsLongConst::castStatically(LgsType* other) {
    return LgsConstExpr::castStatically(other);
}
