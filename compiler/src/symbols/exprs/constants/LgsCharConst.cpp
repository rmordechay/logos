#include "exprs/constants/LgsCharConst.h"

#include "codegen/LgsCodeGen.h"
#include "exprs/constants/LgsStrConst.h"

Value* LgsCharConst::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

std::string LgsCharConst::asText() {
    return type->pname();
}

LgsExpr* LgsCharConst::cast(LgsType* toType, bool explicitly) {
    if (toType->asStr()) {
        return new LgsStrConst(std::string(1, value));
    }
    return this;
}

void LgsCharConst::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}
