#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsFloatConst.h"

string LgsFloat::pName() const {
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

size_t LgsFloat::getSizeBytes() {
    return sizeof(float);
}

string LgsFloat::getStrFormatPart() const {
    return "%f";
}

bool LgsFloat::equals(LgsType* other) {
    return name == other->getIRName();
}

LgsType* LgsFloat::inferBinaryType(LgsType* other) {
    return this;
}
