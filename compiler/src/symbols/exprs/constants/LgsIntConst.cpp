#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"
#include "LgsUtils.h"

Value* LgsIntConst::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::cast(LgsType* toType, const bool explicitly) {
    if (!toType) return this;
    if (toType->isScalar() && type->canCastTo(toType)) {
        setType(toType);
    }
    return this;
}

LgsIntConst* LgsIntConst::clone() {
    return new LgsIntConst(type, value);
}

bool LgsIntConst::equals(LgsExpr* other) {
    assert(0);
}

void LgsIntConst::hashNode(size_t& oldHash) {
    hashNodeInt(oldHash, value);
}

std::string LgsIntConst::asText() {
    return std::to_string(value);
}

void LgsIntConst::setDebugValue(LgsCodeGen& cg) { /* do nothing */}
