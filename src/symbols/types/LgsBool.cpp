#include "types/LgsBool.h"

#include "exprs/unary/constants/LgsBoolConst.h"

const string LgsBool::getName() const {
    return name;
}

Type* LgsBool::getIRType() {
    return Type::getInt1Ty(context);
}

LgsConst* LgsBool::getZeroValue() {
    return new LgsBoolConst(false);
}

LgsType* LgsBool::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsBool::equals(LgsType* other) const {
    return name == other->getName();
}
