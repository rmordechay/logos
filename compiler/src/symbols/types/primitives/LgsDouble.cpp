#include "types/primitives/LgsDouble.h"
#include "exprs/constants/LgsFloatConst.h"
#include "codegen/LgsLLVMGen.h"
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

Type* LgsDouble::getIRType(LgsLLVMGen& cg) {
    return cg.builder.getDoubleTy();
}

Constant* LgsDouble::getRTType(LgsLLVMGen& cg) {
    assert(0);
}

bool LgsDouble::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (other->asGeneric()) return true;
    if (IRName == LgsAny::name) return true;
    return false;
}

Value* LgsDouble::powIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return LgsType::powIR(cg, left, right);
}

llvm::DIType* LgsDouble::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsType* LgsDouble::clone() {
    return this;
}
