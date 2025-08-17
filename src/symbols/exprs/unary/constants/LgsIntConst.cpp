#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

std::string LgsIntConst::pname() {
    return std::to_string(value);
}

void LgsIntConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i32(value);
}

LgsExpr* LgsIntConst::castTo(LgsType* toType) {
    if (toType->asInt()) {
        return this;
    }
    if (toType->asStr()) {
        return new LgsStrConst(std::to_string(value));
    }
    if (toType->asLong()) {
        return new LgsLongConst(value);
    }
    return nullptr;
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(value);
}
