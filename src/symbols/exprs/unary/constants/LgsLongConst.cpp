#include "exprs/unary/constants/LgsLongConst.h"


Value* LgsLongConst::createIRValue(LgsModule* runtime) {
    return runtime->builder.getInt64(value);
}
