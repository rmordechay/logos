#include "types/LgsInt.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsIntConst.h"

size_t LgsInt::getSize() {
    return sizeof(int);
}

string LgsInt::prettyName() const {
    return name;
}

Type* LgsInt::getIRType() {
    return i32Ty;
}

string LgsInt::getIRName() {
    return name;
}

string LgsInt::getFormatStr() {
    return "%d";
}

LgsExpr* LgsInt::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsIntConst(0);
}

LgsType* LgsInt::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsInt::equals(LgsType* other) {
    assert(other);
    return name == other->getIRName();
}
