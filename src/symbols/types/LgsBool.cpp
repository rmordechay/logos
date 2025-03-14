#include "types/LgsBool.h"

const string LgsBool::getName() const {
    return typeName;
}

Type* LgsBool::getIRType() {
    return IRType;
}

LgsConstant* LgsBool::getZeroValue() {
    return new LgsConstant(this, false);
}

bool LgsBool::equals(LgsType* other) const {
    return typeName == other->getName();
}
