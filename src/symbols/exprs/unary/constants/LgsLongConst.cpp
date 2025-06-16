#include "exprs/unary/constants/LgsLongConst.h"


Value* LgsLongConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt64(value);
}
