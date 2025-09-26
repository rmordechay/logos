#include "types/primitives/LgsByte.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

Type* LgsByte::getIRType(LgsLLVMGen& cg) {
    return cg.i8Ty();
}

LgsType* LgsByte::applyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    if (name != IRName) return nullptr;
    if (op == ADD) return extendInt();
    return this;
}

Value* LgsByte::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsByte::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsByte::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsByte::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsByte::modIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateSRem(self, other);
}

Value* LgsByte::eqIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpEQ(self, other);
}

Value* LgsByte::neIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpNE(self, other);
}

Value* LgsByte::ltIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSLT(self, other);
}

Value* LgsByte::gtIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSGT(self, other);
}

Value* LgsByte::geIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSGE(self, other);
}

Value* LgsByte::leIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSLE(self, other);
}

Value* LgsByte::bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateAnd(self, other);
}

Value* LgsByte::bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateOr(self, other);
}

Value* LgsByte::bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateXor(self, other);
}

Value* LgsByte::rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateShl(self, other);
}

Value* LgsByte::lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateLShr(self, other);
}

Value* LgsByte::andIR(LgsLLVMGen& cg, Value* self, Value* other) {
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

Value* LgsByte::orIR(LgsLLVMGen& cg, Value* self, Value* other) {
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

size_t LgsByte::getSizeBytes() {
    return sizeof(int8_t);
}

LgsExpr* LgsByte::getZeroValue() {
    return new LgsIntConst(&LGS_BYTE, false);
}

Lgs_RTType LgsByte::getRTType() {
    return RTT_BYTE;
}

std::string LgsByte::getName() {
    return name;
}

std::string LgsByte::pname() {
    return name;
}

bool LgsByte::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsChar::name) return true;
    if (IRName == LgsShort::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsUInt::name) return true;
    return name == IRName;
}

std::string LgsByte::strFormatPart() const {
    return "%d";
}

json::value LgsByte::asJSON() {
    json::object obj;
    obj["name"] = name;
    return obj;
}
