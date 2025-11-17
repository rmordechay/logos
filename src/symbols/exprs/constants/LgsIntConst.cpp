#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include "utils/LgsUtils.h"

Value* LgsIntConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::staticCast(LgsType* toType, const bool explicitCast) {
    if (type->getName() == toType->getName()) return this;
    if (toType->getName() == LgsAny::name) return this;
    const auto thisSize = type->sizeBytes();
    const auto otherSize = toType->sizeBytes();
    if (toType->isInt) {
        // Widening is always allowed
        if (otherSize >= thisSize) {
            return new LgsIntConst(toType, value);
        }
        return nullptr;
    }
    if (toType->asFloat()) return new LgsFloatConst(&LGS_FLOAT, value);
    if (toType->asDouble()) return new LgsFloatConst(&LGS_DOUBLE, value);
    if (explicitCast && toType->asStr()) return new LgsStrConst(std::to_string(value));
    return nullptr;
}

Value* LgsIntConst::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(IRValue);
    if (type->getName() == toType->getName()) return IRValue;
    if (toType->asGeneric()) return IRValue;
    if (toType->asLong()) {
        return cg.i64(value);
    }
    if (toType->asSize()) {
        return cg.usize(value);
    }
    if (toType->asFloat()) {
        return cg.floatv(value);
    }
    if (toType->asDouble()) {
        return cg.doublev(value);
    }
    if (toType->asStr()) {
        return cg.getIRStr(std::to_string(value));
    }
    assert(0);
}

std::string LgsIntConst::asText() {
    return std::to_string(value);
}

bool LgsIntConst::equals(LgsExpr* other) {
    assert(0);
}

void LgsIntConst::hashNode(size_t& oldHash) {
    hashNodeInt(oldHash, value);
}

Value* LgsIntConst::hashValue(LgsLLVMGen& cg) {
    return IRValue;
}

LgsIntConst* LgsIntConst::clone() {
    return new LgsIntConst(type->clone(), value);
}

void LgsIntConst::setDebugValue(LgsLLVMGen& cg) { /* do nothing */}
