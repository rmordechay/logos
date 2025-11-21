#include "types/primitives/LgsSize.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

size_t LgsSize::sizeBytes() {
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

LgsType* LgsSize::applyBinOp(LgsType* toType, LgsBinOp& op) {
    return applyIntBinOp(toType, op.opType);
}

Value* LgsSize::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsSize::subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(left->loadIR(cg), r);
}

Value* LgsSize::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    auto r = right->loadIR(cg);
    if (!left->type->asVec()) {
        r = cg.builder.CreateZExt(r, getIRType(cg));
    }
    return cg.builder.CreateMul(left->loadIR(cg), r);
}

Value* LgsSize::divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(left->loadIR(cg), r);
}

Value* LgsSize::modIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSRem(left->loadIR(cg), r);
}

Value* LgsSize::bitAndIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAnd(left->loadIR(cg), r);
}

Value* LgsSize::bitOrIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateOr(left->loadIR(cg), r);
}

Value* LgsSize::bitXorIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateXor(left->loadIR(cg), r);
}

Value* LgsSize::rshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateShl(left->loadIR(cg), r);
}

Value* LgsSize::lshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateLShr(left->loadIR(cg), r);
}

Value* LgsSize::eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpEQ(left->loadIR(cg), r);
}

Value* LgsSize::neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpNE(left->loadIR(cg), r);
}

Value* LgsSize::ltIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLT(left->loadIR(cg), r);
}

Value* LgsSize::gtIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGT(left->loadIR(cg), r);
}

Value* LgsSize::geIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGE(left->loadIR(cg), r);
}

Value* LgsSize::leIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLE(left->loadIR(cg), r);
}

Value* LgsSize::andIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return andInt(cg, left, right);
}

Value* LgsSize::orIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return orInt(cg, left, right);
}

Lgs_TypeKind LgsSize::getRTTypeKind() {
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
