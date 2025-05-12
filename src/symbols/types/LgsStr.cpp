#include "types/LgsStr.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "types/LgsChar.h"

size_t LgsStr::getSize() {
    return sizeof(void*);
}

Type* LgsStr::getIRType() {
    return ptrTy;
}

string LgsStr::getIRName() {
    return name;
}

string LgsStr::prettyName() const {
    return name;
}

string LgsStr::getFormatStr() {
    return "%d";
}

LgsExpr* LgsStr::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (dynamic_cast<LgsChar*>(other)) return true;
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