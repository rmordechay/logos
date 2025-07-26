#include "exprs/unary/constants/LgsCharConst.h"

#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"


string LgsCharConst::prettyName() {
    return type->prettyName();
}

Value* LgsCharConst::createIRValue(LgsModule* module) {
    return i8(module, value);
}
