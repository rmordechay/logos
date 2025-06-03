#include "types/LgsStr.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsStrConst.h"

size_t LgsStr::getSizeBytes() {
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

Value* LgsStr::getElement(LgsRuntime* runtime, Value* iterPtr, Value* iPtr) {
    if (isStatic) assert(false);
    const auto i = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    return runtime->builder.CreateInBoundsGEP(baseType->getIRType(), iterPtr, {i});
}

string LgsStr::getStrFormatPart() const {
    return "%s";
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getIRName() == "Any") return true;
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

