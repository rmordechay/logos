#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"

string LgsFloat::prettyName() {
    return name;
}

Type* LgsFloat::getIRType(LgsCodeGen* codeGen) {
    return Type::getFloatTy(codeGen->context);
}

string LgsFloat::getName() {
    return name;
}

LgsExpr* LgsFloat::getZeroValue() {
    return new LgsFloatConst(0.0);
}

size_t LgsFloat::getSizeBytes() {
    return sizeof(float);
}

string LgsFloat::getStrFormatPart() const {
    return "%f";
}

bool LgsFloat::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    return name == IRName;
}