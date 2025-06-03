#include "exprs/unary/constants/LgsLongConst.h"

#include "logos/LgsRuntime.h"

Value* LgsLongConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt64(value);
}

LgsExpr* LgsLongConst::convertExpr(LgsType* other) {
    return LgsConstExpr::convertExpr(other);
}
