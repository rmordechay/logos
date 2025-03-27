#include "types/LgsInt.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsIntConst.h"

Type* LgsInt::IRValue = Type::getInt32Ty(context);

const string LgsInt::getName() const {
    return name;
}

Type* LgsInt::getIRType() {
    return IRValue;
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
