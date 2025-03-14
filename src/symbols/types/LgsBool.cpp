#include "types/LgsBool.h"

#include "constants/LgsBoolConst.h"

const string LgsBool::getName() const {
    return typeName;
}

Type* LgsBool::getIRType() {
    return IRType;
}

LgsConstant* LgsBool::getZeroValue() {
    return new LgsBoolConst(false);
}

bool LgsBool::equals(LgsType* other) const {
    return typeName == other->getName();
}
