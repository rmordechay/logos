#include "types/primitives/LgsFloat.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"

std::pair<Value*, Value*> loadOperands(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    if (self->IRValue->getType()->isIntegerTy()) {
        self->IRValue = cg.builder.CreateSIToFP(self->IRValue, cg.floatTy());
    }
    if (other->IRValue->getType()->isIntegerTy()) {
        other->IRValue = cg.builder.CreateSIToFP(other->IRValue, cg.floatTy());
    }
    return {self->IRValue, other->IRValue};
}

std::string LgsFloat::getName() {
    return name;
}

Type* LgsFloat::getIRType(LgsLLVMGen& cg) {
    return Type::getFloatTy(cg.context);
}

LgsExpr* LgsFloat::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

Lgs_TypeKind LgsFloat::getRTTypeKind() {
    return RTT_FLOAT;
}

size_t LgsFloat::sizeBytes() {
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

LgsType* LgsFloat::applyBinOp(LgsBinaryExpr* binExpr) {
    if (binExpr->right->type->asInt()) return this;
    const auto IRName = binExpr->right->type->getName();
    if (name == IRName) return this;
    return nullptr;
}

Value* LgsFloat::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto [l, r] = loadOperands(cg, self, other);
    return cg.builder.CreateFDiv(l, r);
}