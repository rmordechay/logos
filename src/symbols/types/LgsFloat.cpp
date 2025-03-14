#include "types/LgsFloat.h"

const string LgsFloat::getName() const {
    return typeName;
}

Type* LgsFloat::getIRType() {
    return IRType;
}

LgsConstant* LgsFloat::getZeroValue() {
    return new LgsConstant(this, 0.f);
}

bool LgsFloat::equals(LgsType* other) const {
    return typeName == other->getName();
}
