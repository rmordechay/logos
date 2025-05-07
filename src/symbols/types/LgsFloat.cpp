#include "types/LgsFloat.h"

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsFloatConst.h"

string LgsFloat::prettyName() const {
    return name;
}

Type* LgsFloat::getIRType() {
    return Type::getFloatTy(context);
}

string LgsFloat::getIRName() {
    return name;
}

LgsExpr* LgsFloat::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsFloatConst(0.0);
}

bool LgsFloat::equals(LgsType* other) const {
    return name == other->getIRName();
}

LgsType* LgsFloat::inferBinaryType(LgsType* other) {
    return this;
}
