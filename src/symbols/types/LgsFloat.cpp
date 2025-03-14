#include "types/LgsFloat.h"

#include "constants/LgsFloatConst.h"

const string LgsFloat::getName() const {
    return typeName;
}

Type* LgsFloat::getIRType() {
    return IRType;
}

LgsConstant* LgsFloat::getZeroValue() {
    return new LgsFloatConst(0.0);
}

bool LgsFloat::equals(LgsType* other) const {
    return typeName == other->getName();
}
