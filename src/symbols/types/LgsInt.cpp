#include "types/LgsInt.h"

const string LgsInt::getName() const {
    return typeName;
}

Type* LgsInt::getIRType() {
    return IRType;
}

LgsConstant* LgsInt::getZeroValue() {
    return new LgsConstant(this, 0);
}

bool LgsInt::equals(LgsType* other) const {
    return typeName == other->getName();
}
