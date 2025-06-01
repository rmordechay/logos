#include "exprs/unary/constants/LgsCharConst.h"

Value* LgsCharConst::createIRValue(Module* module) {
    return builder.getInt8(value);
}
