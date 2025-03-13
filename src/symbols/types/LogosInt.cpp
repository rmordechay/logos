#include "types/LogosInt.h"

const string LogosInt::getName() const {
    return typeName;
}

Type* LogosInt::getIRType() {
    return IRType;
}

LogosConstant* LogosInt::getZeroValue() {
    return new LogosConstant(this, 0);
}

bool LogosInt::equals(LogosType* other) const {
    return typeName == other->getName();
}
