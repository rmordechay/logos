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

LgsType* LgsSize::applyBinOp(const LgsBinOpType op, LgsType* other) {
    return applyIntBinOp(op, other);
}

Value* LgsSize::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateAdd(self, r);
}

Value* LgsSize::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSub(self, r);
}

Value* LgsSize::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateMul(self, r);
}

Value* LgsSize::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSDiv(self, r);
}

Value* LgsSize::modIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSRem(self, r);
}

Value* LgsSize::bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateAnd(self, r);
}

Value* LgsSize::bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateOr(self, r);
}

Value* LgsSize::bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateXor(self, r);
}

Value* LgsSize::rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateShl(self, r);
}

Value* LgsSize::lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateLShr(self, r);
}

Value* LgsSize::eqIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateICmpEQ(self, r);
}

Value* LgsSize::neIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateICmpNE(self, r);
}

Value* LgsSize::ltIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateICmpSLT(self, r);
}

Value* LgsSize::gtIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateICmpSGT(self, r);
}

Value* LgsSize::geIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateICmpSGE(self, r);
}

Value* LgsSize::leIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateICmpSLE(self, r);
}

Value* LgsSize::andIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(other, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.false_(), currentBlock);
    phi->addIncoming(other, rightBlock);
    return phi;
}

Value* LgsSize::orIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(self, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.true_(), currentBlock);
    phi->addIncoming(other, rightBlock);
    return phi;
}

Lgs_rttype LgsSize::getRTType() {
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
