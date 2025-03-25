#include "types/LgsFloat.h"

#include "exprs/unary/constants/LgsFloatConst.h"

const string LgsFloat::getName() const {
    return name;
}

Type* LgsFloat::getIRType() {
    return Type::getFloatTy(context);
}

LgsConst* LgsFloat::getZeroValue() {
    return new LgsFloatConst(0.0);
}

bool LgsFloat::equals(LgsType* other) const {
    return name == other->getName();
}

LgsType* LgsFloat::inferBinaryType(LgsType* other) {
    return this;
}
