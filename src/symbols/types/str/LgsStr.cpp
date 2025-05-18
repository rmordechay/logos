#include "types/str/LgsStr.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsStrConst.h"

int LgsStr::getDims() {
    return 1;
}

size_t LgsStr::getSize() {
    return sizeof(void*);
}

string LgsStr::getIRName() {
    return name;
}

Type* LgsStr::getIRType() {
    return ptrTy;
}

string LgsStr::prettyName() const {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) {
    return this;
}

LgsType* LgsStr::createInnerType(size_t indexRange, LgsIndex* index) const {
    return baseType;
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    return name == other->getIRName();
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

