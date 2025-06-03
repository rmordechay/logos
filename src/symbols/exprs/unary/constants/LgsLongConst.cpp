#include "exprs/unary/constants/LgsLongConst.h"

Value* LgsLongConst::createIRValue(LgsRuntime* runtime) {
    return builder.getInt64(value);
}

LgsExpr* LgsLongConst::convertExpr(LgsType* other) {
    return LgsConstExpr::convertExpr(other);
}
