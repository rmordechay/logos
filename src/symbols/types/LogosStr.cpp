#include "types/LogosStr.h"
#include "constants/LogosConstant.h"

const string LogosStr::getName() const {
    return typeName;
}

Type* LogosStr::getIRType() {
    return IRType;
}

LogosConstant* LogosStr::getZeroValue() {
    return new LogosConstant(this, 0);
}

bool LogosStr::equals(LogosType* other) const {
    return typeName == other->getName();
}
