#include "types/primitives/LgsFloat.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsDouble.h"

std::pair<Value*, Value*> loadOperands(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.floatTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.floatTy());
    }
    return {l, r};
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

Constant* LgsFloat::getRTType(LgsLLVMGen& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), RTT_FLOAT, cg.null());
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

LgsType* LgsFloat::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

Value* LgsFloat::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadOperands(cg, left, right);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadOperands(cg, left, right);
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadOperands(cg, left, right);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadOperands(cg, left, right);
    return cg.builder.CreateFDiv(l, r);
}

llvm::DIType* LgsFloat::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsType* LgsFloat::clone() {
    return this;
}
