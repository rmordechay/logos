#include "exprs/unary/constants/LgsLongConst.h"


Value* LgsLongConst::createIRValue(LgsModule* module) {
    return module->builder.getInt64(value);
}
