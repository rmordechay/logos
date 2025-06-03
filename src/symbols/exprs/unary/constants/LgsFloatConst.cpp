#include "exprs/unary/constants/LgsFloatConst.h"

#include "logos/LgsRuntime.h"

Value* LgsFloatConst::createIRValue(LgsRuntime* runtime) {
    return ConstantFP::get(runtime->builder.getFloatTy(), value);
}
