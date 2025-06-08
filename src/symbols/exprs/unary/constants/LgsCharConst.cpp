#include "exprs/unary/constants/LgsCharConst.h"



Value* LgsCharConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt8(value);
}
