#include "types/LogosFloat.h"

const string LogosFloat::getName() const {
    return typeName;
}

Type* LogosFloat::getIRType() {
    return IRType;
}

LogosConstant* LogosFloat::getZeroValue() {
    return new LogosConstant(this, 0.f);
}

bool LogosFloat::equals(LogosType* other) const {
    return typeName == other->getName();
}
