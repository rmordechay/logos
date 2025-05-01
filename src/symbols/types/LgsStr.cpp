#include "types/LgsStr.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsConstExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "types/LgsChar.h"

const string LgsStr::getName() const {
    return name;
}

Type* LgsStr::getIRType() {
    return ptrTy;
}

Type* LgsStr::getUnderlyingIRType() {
    assert(false);
}

LgsExpr* LgsStr::getZeroValue() {
    if (nullable) return new LgsNull();
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsStr::equals(LgsType* other) const {
    assert(other);
    if (dynamic_cast<LgsChar*>(other)) return true;
    return name == other->getName();
}

void LgsStr::cleanStr(string& value) {
    value.erase(0, 1);
    value.pop_back();
}

/**
 * FNV-1a 32-bit hash
 */
uint32_t LgsStr::hashString(const string& str) {
    uint32_t hash = 2166136261u;
    for (const auto c : str) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}