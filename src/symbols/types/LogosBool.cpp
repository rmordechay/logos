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

LogosField* LogosBool::getField(const string& name) {
    return nullptr;
}

LogosMethodImpl* LogosBool::getMethod(const string& name) {
    return nullptr;
}

bool LogosBool::equals(LogosType* other) const {
    return typeName == other->getName();
}
