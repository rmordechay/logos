#include "exprs/unary/constants/LgsShortConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

#include "utils/LgsUtils.h"


std::string LgsShortConst::prettyName() {
    return std::to_string(value);
}

void LgsShortConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i16(value);
}

LgsExpr* LgsShortConst::castTo(LgsType* toType) {
    if (toType->asShort()) {
        return this;
    }
    if (toType->asStr()) {
        return new LgsStrConst(std::to_string(value));
    }
    return nullptr;
}

LgsExpr* LgsShortConst::clone() {
    return new LgsShortConst(value);
}
