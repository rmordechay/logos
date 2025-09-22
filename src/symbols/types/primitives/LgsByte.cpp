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

Value* LgsByte::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsByte::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsByte::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsByte::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateUDiv(l, r);
}

Value* LgsByte::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSRem(l, r);
}

Value* LgsByte::eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpEQ(l, r);
}

Value* LgsByte::neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpNE(l, r);
}

Value* LgsByte::ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLT(l, r);
}

Value* LgsByte::gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGT(l, r);
}

Value* LgsByte::geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGE(l, r);
}

Value* LgsByte::leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLE(l, r);
}

Value* LgsByte::bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAnd(l, r);
}

Value* LgsByte::bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateOr(l, r);
}

Value* LgsByte::bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateXor(l, r);
}

Value* LgsByte::rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateShl(l, r);
}

Value* LgsByte::lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateLShr(l, r);
}

Value* LgsByte::andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(other->IRValue, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.builder.getFalse(), currentBlock);
    phi->addIncoming(other->IRValue, rightBlock);
    return phi;
}

Value* LgsByte::orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(self->IRValue, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.builder.getTrue(), currentBlock);
    phi->addIncoming(other->IRValue, rightBlock);
    return phi;
}

size_t LgsByte::getSizeBytes() {
    return sizeof(int8_t);
}

LgsExpr* LgsByte::getZeroValue() {
    return new LgsIntConst(&LGS_BYTE, false);
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
