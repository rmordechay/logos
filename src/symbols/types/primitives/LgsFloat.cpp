#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsInt.h"

json::value LgsFloat::asJSON() {
    assert(0);
}

std::string LgsFloat::pname() {
    return name;
}

Type* LgsFloat::getIRType(LgsCodeGen& codeGen) {
    return Type::getFloatTy(codeGen.context);
}

std::string LgsFloat::getName() {
    return name;
}

LgsExpr* LgsFloat::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

size_t LgsFloat::getSizeBytes() {
    return sizeof(float);
}

std::string LgsFloat::strFormatPart() const {
    return "%f";
}

bool LgsFloat::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsDouble::name) return true;
    return false;
}