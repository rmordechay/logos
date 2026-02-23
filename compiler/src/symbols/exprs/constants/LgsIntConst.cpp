#include "exprs/constants/LgsIntConst.h"
#include <assert.h>
#include <limits>
#include "LgsUtils.h"
#include "types/primitives/LgsBool.h"
#include "LgsType.h"

LgsExpr* LgsIntConst::cast(LgsType* toType, const bool explicitly) {
    if (!toType || !toType->isScalar()) return this;
    if (!inRange(toType)) return this;
    setType(toType);
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
    if (!type->asBool()) return std::to_string(value);
    return value ? LgsBool::trueLiteral : LgsBool::falseLiteral;
}

template<typename T>
bool inRangeGeneric(int64_t value) {
    if constexpr (std::is_unsigned_v<T>) {
        if (value < 0) return false;
        return static_cast<uint64_t>(value) <= std::numeric_limits<T>::max();
    } else {
        return value >= std::numeric_limits<T>::lowest() && value <= std::numeric_limits<T>::max();
    }
}

bool LgsIntConst::inRange(LgsType* toType) const {
    if (toType->asBool()) return value == 0 || value == 1;
    if (toType->asShort()) return inRangeGeneric<int16_t>(value);
    if (toType->asInt()) return inRangeGeneric<int32_t>(value);
    if (toType->asLong()) return inRangeGeneric<int64_t>(value);
    if (toType->asSize()) return inRangeGeneric<size_t>(value);
    if (toType->asFloat()) return inRangeGeneric<float>(value);
    if (toType->asDouble()) return inRangeGeneric<double>(value);
    if (toType->asUInt()) return inRangeGeneric<uint32_t>(value);
    if (toType->asChar() || toType->asByte()) return inRangeGeneric<int8_t>(value);
    return false;
}

void LgsIntConst::setDebugValue(LgsCodeGen& cg) {}