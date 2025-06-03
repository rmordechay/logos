#include "types/primitives/LgsFloat.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsFloatConst.h"

string LgsFloat::prettyName() const {
    return name;
}

Type* LgsFloat::getIRType() {
    return floatTy;
}

string LgsFloat::getIRName() {
    return name;
}

LgsExpr* LgsFloat::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsFloatConst(0.0);
}

bool LgsFloat::equals(LgsType* other) {
    return name == other->getIRName();
}

LgsType* LgsFloat::inferBinaryType(LgsType* other) {
    return this;
}
