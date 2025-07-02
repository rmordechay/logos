#include "exprs/unary/constants/LgsCharConst.h"



Value* LgsCharConst::createIRValue(LgsModule* module) {
    return module->builder.getInt8(value);
}
