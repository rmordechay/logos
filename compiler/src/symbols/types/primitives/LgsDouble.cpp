#include "types/primitives/LgsDouble.h"
#include "exprs/constants/LgsFloatConst.h"
#include "codegen/LgsCgModule.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"

std::string LgsDouble::getName() {
    return name;
}

size_t LgsDouble::sizeBytes() {
    return sizeof(double_t);
}

LgsExpr* LgsDouble::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

std::string LgsDouble::strFormatPart() const {
    return "%f";
}

Type* LgsDouble::getIRType(LgsCgModule& cg) {
    return cg.builder.getDoubleTy();
}

Constant* LgsDouble::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), RTT_DOUBLE, cg.null());
}

bool LgsDouble::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (other->asGeneric()) return true;
    if (IRName == LgsAny::name) return true;
    return false;
}

Value* LgsDouble::powIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return LgsType::powIR(cg, left, right);
}

llvm::DIType* LgsDouble::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsDouble::clone() {
    return this;
}
