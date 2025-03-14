#include "types/LgsBool.h"

#include "constants/LgsBoolConst.h"

const string LgsBool::getName() const {
    return name;
}

Type* LgsBool::getIRType() {
    return IRType;
}

LgsConst* LgsBool::getZeroValue() {
    return new LgsBoolConst(false);
}

LgsType* LgsBool::inferBinaryType(LgsType* other) const {
    return other;
}

bool LgsBool::equals(LgsType* other) const {
    return name == other->getName();
}
