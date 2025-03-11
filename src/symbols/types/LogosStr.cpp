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

LogosField* LogosStr::getField(const string& name) {
    return nullptr;
}

LogosMethodImpl* LogosStr::getMethod(const string& name) {
    return nullptr;
}

bool LogosStr::equals(LogosType* other) const {
    return typeName == other->getName();
}
