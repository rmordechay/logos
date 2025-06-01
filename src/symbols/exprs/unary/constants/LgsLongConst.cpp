#include "exprs/unary/constants/LgsLongConst.h"

Value* LgsLongConst::createIRValue(CodegenMetadata* metadata) {
    return metadata->builder.getInt64(value);
}

LgsExpr* LgsLongConst::convertExpr(LgsType* other) {
    return LgsConstExpr::convertExpr(other);
}
