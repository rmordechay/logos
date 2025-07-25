#include "exprs/unary/constants/LgsLongConst.h"

#include "utils/LgsUtils.h"


Value* LgsLongConst::createIRValue(LgsModule* module) {
    return i64(module, value);
}
