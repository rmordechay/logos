#include "types/primitives/LgsInt.h"
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsSize.h"
#include <llvm/IR/DIBuilder.h>

size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

Type* LgsInt::getIRType(LgsLLVMGen& cg) {
    return cg.i32Ty();
}

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(&LGS_INT, 0);
}

Lgs_RTType LgsInt::getRTType() {
    return RTT_INT;
}

bool LgsInt::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsInt::applyBinOp(LgsBinaryExpr* binExpr) {
    return applyIntBinOp(binExpr->op, binExpr->left->type);
}

Value* LgsInt::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsInt::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsInt::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsInt::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsInt::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateSRem(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateAnd(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateOr(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateXor(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateShl(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateLShr(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateICmpEQ(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateICmpNE(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateICmpSLT(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateICmpSGT(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateICmpSGE(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateICmpSLE(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
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

Value* LgsInt::orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
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

std::string LgsInt::strFormatPart() const {
    return "%d";
}

std::string LgsInt::getName() {
    return name;
}

DIBasicType* LgsInt::getDebugType(LgsLLVMGen& cg) {
    return cg.debugger.diBuilder->createBasicType(name, 32, llvm::dwarf::DW_ATE_signed);
}