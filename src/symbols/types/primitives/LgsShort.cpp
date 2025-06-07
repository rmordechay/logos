#include "types/primitives/LgsShort.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsShortConst.h"
#include "logos/LgsRuntime.h"

size_t LgsShort::getSizeBytes() {
    return sizeof(short);
}

Type* LgsShort::getIRType() {
    return Type::getInt16Ty(context);
}

string LgsShort::prettyName() const {
    return name;
}

string LgsShort::getIRName() {
    return name;
}

LgsExpr* LgsShort::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsShortConst(0);
}

LgsType* LgsShort::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsShort::equals(LgsType* other) {
    assert(other);
    if (other->getIRName() == "Any") return true;
    return name == other->getIRName();
}

string LgsShort::getStrFormatPart() const {
    return "%d";
}

LgsType* LgsShort::clone() {
    return this;
}

