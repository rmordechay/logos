#include "types/LgsChar.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsCharConst.h"

const string LgsChar::getName() const {
    return name;
}

Type* LgsChar::getIRType() {
    return Type::getInt8Ty(context);
}

LgsExpr* LgsChar::getZeroValue() {
    if (nullable) return new LgsNull();
    return new LgsCharConst('0');
}

LgsType* LgsChar::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsChar::equals(LgsType* other) const {
    return name == other->getName();
}
