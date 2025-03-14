#include "types/LgsString.h"
#include "constants/LgsConstant.h"

const string LgsString::getName() const {
    return typeName;
}

Type* LgsString::getIRType() {
    return IRType;
}

LgsConstant* LgsString::getZeroValue() {
    return new LgsConstant(this, 0);
}

bool LgsString::equals(LgsType* other) const {
    return typeName == other->getName();
}
