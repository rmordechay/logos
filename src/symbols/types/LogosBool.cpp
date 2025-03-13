#include "types/LogosBool.h"

const string LogosBool::getName() const {
    return typeName;
}

Type* LogosBool::getIRType() {
    return IRType;
}

LogosConstant* LogosBool::getZeroValue() {
    return new LogosConstant(this, false);
}

bool LogosBool::equals(LogosType* other) const {
    return typeName == other->getName();
}
