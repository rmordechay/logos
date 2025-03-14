#include "types/LgsStr.h"

#include "constants/LgsConstant.h"
#include "constants/LgsStrConst.h"

const string LgsStr::getName() const {
    return typeName;
}

Type* LgsStr::getIRType() {
    return IRType;
}

LgsConstant* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

bool LgsStr::equals(LgsType* other) const {
    return typeName == other->getName();
}
