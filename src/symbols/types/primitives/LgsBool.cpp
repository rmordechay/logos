#include "types/primitives/LgsBool.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsIterable.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

Type* LgsBool::getIRType(LgsLLVMGen& cg) {
    return cg.i1Ty();
}

LgsType* LgsBool::applyOp(LgsType* other, LgsOperator op) {
    const auto IRName = other->getName();
    if (name != IRName) return nullptr;
    if (op == ADD) return extendInt();
    return this;
}

Value* LgsBool::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return addIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return subIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return mulIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return divIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return modIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return eqIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return neIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return ltIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return gtIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return geIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return leIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return bitAndIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return bitOrIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return bitXorIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return rshiftIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return lshiftIR(cg, self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return andIR(cg, self->IRValue, other->IRValue);
}

Value* LgsBool::orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return orIR(cg, self->IRValue, other->IRValue);
}

Value* LgsBool::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsBool::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsBool::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsBool::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto l = cg.builder.CreateZExt(self, getIRType(cg));
    const auto r = cg.builder.CreateZExt(other, getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsBool::modIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateSRem(self, other);
}

Value* LgsBool::eqIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpEQ(self, other);
}

Value* LgsBool::neIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpNE(self, other);
}

Value* LgsBool::ltIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSLT(self, other);
}

Value* LgsBool::gtIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSGT(self, other);
}

Value* LgsBool::geIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSGE(self, other);
}

Value* LgsBool::leIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateICmpSLE(self, other);
}

Value* LgsBool::bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateAnd(self, other);
}

Value* LgsBool::bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateOr(self, other);
}

Value* LgsBool::bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateXor(self, other);
}

Value* LgsBool::rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateShl(self, other);
}

Value* LgsBool::lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) {
    return cg.builder.CreateLShr(self, other);
}

Value* LgsBool::andIR(LgsLLVMGen& cg, Value* self, Value* other) {
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

Value* LgsBool::orIR(LgsLLVMGen& cg, Value* self, Value* other) {
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

std::string LgsBool::getName() {
    return name;
}

std::string LgsBool::pname() {
    return name;
}

json::value LgsBool::asJSON() {
    json::object obj;
    obj["name"] = name;
    return obj;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

Lgs_RTType LgsBool::getRTType() {
    return RTT_BOOL;
}

std::string LgsBool::strFormatPart() const {
    return "%s";
}

size_t LgsBool::getSizeBytes() {
    return sizeof(bool);
}

bool LgsBool::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsUInt::name) return true;
    return name == otherName;
}
