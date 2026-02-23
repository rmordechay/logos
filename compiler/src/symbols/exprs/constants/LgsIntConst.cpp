#include "exprs/constants/LgsIntConst.h"
#include <assert.h>
#include <limits>
#include "LgsUtils.h"
#include "types/primitives/LgsBool.h"
#include "LgsType.h"

LgsExpr* LgsIntConst::cast(LgsType* toType, const bool explicitly) {
    if (!toType || !toType->isScalar()) return this;
    if (!inRange(value, toType)) return this;
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

void LgsIntConst::setDebugValue(LgsCodeGen& cg) {

}