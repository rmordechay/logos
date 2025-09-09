#include "types/primitives/LgsFloat.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsNull.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"

json::value LgsFloat::asJSON() {
    assert(0);
}

std::string LgsFloat::pname() {
    return name;
}

Type* LgsFloat::getIRType(LgsLLVMGen& cg) {
    return Type::getFloatTy(cg.context);
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
    return "%.3f";
}

bool LgsFloat::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsDouble::name) return true;
    return false;
}

bool LgsFloat::canAssignTo(LgsType* other, LgsAssignType op) {
    return canCastTo(other);
}

bool LgsFloat::canApplyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    return false;
}
