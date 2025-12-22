#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"
#include "LgsUtils.h"

Value* LgsIntConst::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsIntConst::castImplicitly(LgsType* toType) {
    if (!toType) return;
    if (!type->canCastTo(toType)) return;
    setType(toType);
}

LgsExpr* LgsIntConst::castExplicitly(LgsType* toType) {
    if (type->getName() == toType->getName()) return this;
    if (toType->getName() == LgsAny::name) return this;
    const auto thisSize = type->sizeBytes();
    const auto otherSize = toType->sizeBytes();
    if (toType->isInt) {
        // Widening is always allowed
        if (otherSize >= thisSize) {
            setType(toType);
            return this;
        }
        return nullptr;
    }
    if (toType->asFloat()) return new LgsFloatConst(&LGS_FLOAT, value);
    if (toType->asDouble()) return new LgsFloatConst(&LGS_DOUBLE, value);
    if (toType->asStr()) return new LgsStrConst(std::to_string(value));
    return nullptr;
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

Value* LgsIntConst::hashValue(LgsCgModule& cg) {
    return IRValue;
}

std::string LgsIntConst::asText() {
    return std::to_string(value);
}

void LgsIntConst::setDebugValue(LgsCgModule& cg) { /* do nothing */}
