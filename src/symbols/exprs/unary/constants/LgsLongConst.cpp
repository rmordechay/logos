#include "exprs/unary/constants/LgsLongConst.h"

#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"


string LgsLongConst::prettyName() {
    return type->prettyName();
}

Value* LgsLongConst::createIRValue(LgsModule* module) {
    return i64(module, value);
}
