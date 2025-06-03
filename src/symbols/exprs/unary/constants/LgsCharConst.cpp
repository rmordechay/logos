#include "exprs/unary/constants/LgsCharConst.h"

#include "logos/LgsRuntime.h"

Value* LgsCharConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt8(value);
}
