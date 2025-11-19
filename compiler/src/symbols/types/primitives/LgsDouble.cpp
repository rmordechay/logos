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

Lgs_TypeKind LgsDouble::getRTTypeKind() {
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
    if (other->asGeneric()) return true;
    if (IRName == LgsAny::name) return true;
    return false;
}

LgsExpr* LgsDouble::powConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsFloatConst(&LGS_DOUBLE, std::pow(*const1, *const2));
}

Value* LgsDouble::powIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return LgsType::powIR(cg, left, right);
}
