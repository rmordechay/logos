#include "exprs/unary/constants/LgsCharConst.h"

#include "utils/LgsUtils.h"


Value* LgsCharConst::createIRValue(LgsModule* module) {
    return i8(module, value);
}
