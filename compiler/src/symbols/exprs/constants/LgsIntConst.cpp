#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsLong.h"
#include "LgsUtils.h"
#include "types/primitives/LgsBool.h"

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

bool LgsIntConst::inRange(LgsType* toType) const {
    if (toType->asBool()) return value == 0 || value == 1;
    if (toType->asShort()) return value >= std::numeric_limits<int16_t>::lowest() && value <= std::numeric_limits<int16_t>::max();
    if (toType->asInt()) return value >= std::numeric_limits<int32_t>::lowest() && value <= std::numeric_limits<int32_t>::max();
    if (toType->asLong()) return value >= std::numeric_limits<int64_t>::lowest() && value <= std::numeric_limits<int64_t>::max();
    if (toType->asFloat()) return value >= std::numeric_limits<float>::lowest() && value <= std::numeric_limits<float>::max();
    if (toType->asDouble()) return value >= std::numeric_limits<double>::lowest() && value <= std::numeric_limits<double>::max();
    if (toType->asUInt()) return value >= 0 && value <= std::numeric_limits<uint32_t>::max();
    if (toType->asChar() || toType->asByte()) return value >= std::numeric_limits<int8_t>::lowest() && value <= std::numeric_limits<int8_t>::max();
    return false;
}

void LgsIntConst::setDebugValue(LgsCodeGen& cg) {}