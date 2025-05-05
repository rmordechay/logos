#include "types/LgsInt.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsIntConst.h"

const string LgsInt::getPrettyName() const {
    return name;
}

Type* LgsInt::getIRType() {
    return i32Ty;
}

LgsExpr* LgsInt::getZeroValue() {
    if (nullable) return new LgsNull();
    return new LgsIntConst(0);
}

LgsType* LgsInt::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsInt::equals(LgsType* other) const {
    assert(other);
    return name == other->getPrettyName();
}
