#include "types/primitives/LgsSize.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

size_t LgsSize::sizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType(LgsCgModule& cg) {
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

Value* LgsSize::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsSize::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(left->loadIR(cg), r);
}

Value* LgsSize::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    auto r = right->loadIR(cg);
    if (!left->type->asVec()) {
        r = cg.builder.CreateZExt(r, getIRType(cg));
    }
    return cg.builder.CreateMul(left->loadIR(cg), r);
}

Value* LgsSize::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(left->loadIR(cg), r);
}

Value* LgsSize::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSRem(left->loadIR(cg), r);
}

Value* LgsSize::bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAnd(left->loadIR(cg), r);
}

Value* LgsSize::bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateOr(left->loadIR(cg), r);
}

Value* LgsSize::bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateXor(left->loadIR(cg), r);
}

Value* LgsSize::rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateShl(left->loadIR(cg), r);
}

Value* LgsSize::lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* other) {
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateLShr(left->loadIR(cg), r);
}

Value* LgsSize::eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpEQ(left->loadIR(cg), r);
}

Value* LgsSize::neIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpNE(left->loadIR(cg), r);
}

Value* LgsSize::ltIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLT(left->loadIR(cg), r);
}

Value* LgsSize::gtIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGT(left->loadIR(cg), r);
}

Value* LgsSize::geIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSGE(left->loadIR(cg), r);
}

Value* LgsSize::leIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateICmpSLE(left->loadIR(cg), r);
}

Value* LgsSize::andIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return andInt(cg, left, right);
}

Value* LgsSize::orIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return orInt(cg, left, right);
}

Constant* LgsSize::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), RTT_SIZE, cg.null());
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

llvm::DIType* LgsSize::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsSize::clone() {
    return this;
}
