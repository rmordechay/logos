#include "exprs/unary/constants/LgsShortConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"


string LgsShortConst::prettyName() {
    return to_string(value);
}

Value* LgsShortConst::createIRValue(LgsModule* module) {
    return i16(module, value);
}

LgsExpr* LgsShortConst::convertExpr(LgsType* toType) {
    if (toType->asShort()) {
        return this;
    }
    if (toType->asStr()) {
        return new LgsStrConst(to_string(value));
    }
    assert(0);
}

LgsExpr* LgsShortConst::clone() {
    return new LgsShortConst(value);
}
