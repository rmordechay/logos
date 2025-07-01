#include "exprs/unary/constants/LgsCharConst.h"



Value* LgsCharConst::createIRValue(LgsModule* runtime) {
    return runtime->builder.getInt8(value);
}
