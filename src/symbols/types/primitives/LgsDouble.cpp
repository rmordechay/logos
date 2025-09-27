#include "types/primitives/LgsDouble.h"
#include "exprs/constants/LgsFloatConst.h"
#include "../codegen/LgsLLVMGen.h"
#include "types/LgsAny.h"

std::string LgsDouble::getName() {
    return name;
}

json::value LgsDouble::asJsonStr() {
    assert(0);
}

size_t LgsDouble::getSizeBytes() {
    return sizeof(double_t);
}

LgsExpr* LgsDouble::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

Lgs_RTType LgsDouble::getRTType() {
    return RTT_DOUBLE;
}

std::string LgsDouble::strFormatPart() const {
    return "%f";
}

Type* LgsDouble::getIRType(LgsLLVMGen& cg) {
    return cg.builder.getDoubleTy();
}

bool LgsDouble::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (IRName == LgsAny::name) return true;
    return false;
}
