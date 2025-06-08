#include "types/LgsStr.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

size_t LgsStr::getSizeBytes() {
    return sizeof(void*);
}

string LgsStr::getIRName() {
    return name;
}

Type* LgsStr::getIRType() {
    return PointerType::getUnqual(context);
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

string LgsStr::getStrFormatPart() const {
    return "%s";
}

Value* LgsStr::getLength(LgsRuntime* runtime, LgsExpr* expr) {
    return len.call(runtime, {expr});
}

Value* LgsStr::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    return getLength(runtime, expr);
}

Value* LgsStr::callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmpty.call(runtime, {expr});
}

Value* LgsStr::callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmpty.call(runtime, {expr});
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

