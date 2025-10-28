#include "types/primitives/LgsSize.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

size_t LgsSize::getSizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType(LgsLLVMGen& cg) {
    return cg.sizeTy();
}

std::string LgsSize::getName() {
    return name;
}

LgsExpr* LgsSize::getZeroValue() {
    return new LgsIntConst(this, 0);
}

LgsType* LgsSize::applyBinOp(LgsBinaryExpr* binExpr) {
    return applyIntBinOp(binExpr->op, binExpr->left->type);
}

Value* LgsSize::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsSize::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(self->loadIR(cg), r);
}

Value* LgsSize::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(self->loadIR(cg), r);
}

Value* LgsSize::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(self->loadIR(cg), r);
}

Value* LgsSize::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSRem(self->loadIR(cg), r);
}

Value* LgsSize::bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAnd(self->loadIR(cg), r);
}

Value* LgsSize::bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateOr(self->loadIR(cg), r);
}

Value* LgsSize::bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateXor(self->loadIR(cg), r);
}

Value* LgsSize::rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateShl(self->loadIR(cg), r);
}

Value* LgsSize::lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateLShr(self->loadIR(cg), r);
}

Value* LgsSize::eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpEQ(self->loadIR(cg), r);
}

Value* LgsSize::neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpNE(self->loadIR(cg), r);
}

Value* LgsSize::ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLT(self->loadIR(cg), r);
}

Value* LgsSize::gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGT(self->loadIR(cg), r);
}

Value* LgsSize::geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGE(self->loadIR(cg), r);
}

Value* LgsSize::leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLE(self->loadIR(cg), r);
}

Value* LgsSize::andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(other->IRValue, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.false_(), currentBlock);
    phi->addIncoming(other->IRValue, rightBlock);
    return phi;
}

Value* LgsSize::orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(self->IRValue, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.true_(), currentBlock);
    phi->addIncoming(other->IRValue, rightBlock);
    return phi;
}

Lgs_RTType LgsSize::getRTType() {
    return RTT_SIZE;
}

bool LgsSize::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsLong::name) return true;
    return name == IRName;
}

std::string LgsSize::strFormatPart() const {
    return "%zu";
}
