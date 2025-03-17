#include "types/LgsInt.h"

#include "exprs/unary/constants/LgsIntConst.h"

const string LgsInt::getName() const {
    return name;
}

Type* LgsInt::getIRType() {
    return IRType;
}

LgsConst* LgsInt::getZeroValue() {
    return new LgsIntConst(0);
}

LgsType* LgsInt::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsInt::equals(LgsType* other) const {
    return name == other->getName();
}
