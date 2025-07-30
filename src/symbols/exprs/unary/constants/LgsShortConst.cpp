#include "exprs/unary/constants/LgsShortConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

#include "utils/LgsUtils.h"


string LgsShortConst::prettyName() {
    return to_string(value);
}

Value* LgsShortConst::createIRValue(LgsCodeGen* codeGen) {
    return codeGen->i16(value);
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
