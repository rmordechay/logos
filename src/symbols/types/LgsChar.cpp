#include "types/LgsChar.h"

#include "exprs/unary/constants/LgsCharConst.h"

const string LgsChar::getName() const {
    return name;
}

Type* LgsChar::getIRType() {
    return IRType;
}

LgsConst* LgsChar::getZeroValue() {
    return new LgsCharConst('a');
}

LgsType* LgsChar::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsChar::equals(LgsType* other) const {
    return name == other->getName();
}
