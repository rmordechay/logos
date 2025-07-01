#include "exprs/LgsNullValue.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"

string LgsFloat::prettyName() const {
    return name;
}

Type* LgsFloat::getIRType(LLVMContext& context) {
    return Type::getFloatTy(context);
}

string LgsFloat::getIRName() {
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
    const auto IRName = other->getIRName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    return name == IRName;
}