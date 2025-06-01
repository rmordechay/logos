#include "exprs/unary/constants/LgsLongConst.h"

Value* LgsLongConst::createIRValue(Module* module) {
    return builder.getInt64(value);
}

LgsExpr* LgsLongConst::convertExpr(LgsType* other) {
    return LgsConstExpr::convertExpr(other);
}
