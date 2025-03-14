#include "types/LgsString.h"
#include "constants/LgsConstant.h"
#include "constants/LgsStrConst.h"

const string LgsString::getName() const {
    return typeName;
}

Type* LgsString::getIRType() {
    return IRType;
}

LgsConstant* LgsString::getZeroValue() {
    return new LgsStrConst("");
}

bool LgsString::equals(LgsType* other) const {
    return typeName == other->getName();
}
