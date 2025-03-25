#include "types/LgsInt.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsIntConst.h"

const string LgsInt::getName() const {
    return name;
}

Type* LgsInt::getIRType() {
    return Type::getInt32Ty(context);
}

LgsExpr* LgsInt::getZeroValue() {
    if (nullable) return new LgsNull();
    return new LgsIntConst(0);
}

LgsType* LgsInt::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsInt::equals(LgsType* other) const {
    return name == other->getName();
}
