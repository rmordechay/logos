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

LogosField* LogosFloat::getField(const string& name) {
    return nullptr;
}

LogosMethodImpl* LogosFloat::getMethod(const string& name) {
    return nullptr;
}

bool LogosFloat::equals(LogosType* other) const {
    return typeName == other->getName();
}
