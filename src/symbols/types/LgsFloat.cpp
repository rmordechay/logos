#include "types/LgsFloat.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsFloatConst.h"

const string LgsFloat::getPrettyName() const {
    return name;
}

Type* LgsFloat::getIRType() {
    return Type::getFloatTy(context);
}

LgsExpr* LgsFloat::getZeroValue() {
    if (nullable) return new LgsNull();
    return new LgsFloatConst(0.0);
}

bool LgsFloat::equals(LgsType* other) const {
    return name == other->getPrettyName();
}

LgsType* LgsFloat::inferBinaryType(LgsType* other) {
    return this;
}
