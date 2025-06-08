#include "types/primitives/LgsInt.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsIntConst.h"

size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

string LgsInt::prettyName() const {
    return name;
}

Type* LgsInt::getIRType() {
    return Type::getInt32Ty(context);
}

string LgsInt::getIRName() {
    return name;
}

LgsExpr* LgsInt::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsIntConst(0);
}

LgsType* LgsInt::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsInt::equals(LgsType* other) {
    if (other->getIRName() == "Any") return true;
    return name == other->getIRName();
}

string LgsInt::getStrFormatPart() const {
    return "%d";
}

LgsType* LgsInt::clone() {
    return this;
}
