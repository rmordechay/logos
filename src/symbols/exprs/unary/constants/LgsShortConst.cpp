#include "exprs/unary/constants/LgsShortConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "types/LgsStr.h"

string LgsShortConst::prettyName() {
    return to_string(value);
}

Value* LgsShortConst::createIRValue(LgsRuntime* runtime) {
    return runtime->builder.getInt16(value);
}

LgsExpr* LgsShortConst::convertExpr(LgsType* other) {
    if (other->asStr()) {
        return new LgsStrConst(to_string(value));
    }
    assert(false);
}

LgsExpr* LgsShortConst::clone() {
    return new LgsShortConst(value);
}
