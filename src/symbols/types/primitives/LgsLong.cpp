#include "types/primitives/LgsLong.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"

Type* LgsLong::getIRType(LgsLLVMGen& cg) {
    return cg.i64Ty();
}

size_t LgsLong::getSizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsIntConst(&LGS_LONG, 0);
}

Lgs_TypeKind LgsLong::getRTTypeKind() {
    return RTT_LONG;
}

LgsType* LgsLong::applyBinOp(LgsBinaryExpr* binExpr) {
    return applyIntBinOp(binExpr->op, binExpr->left->type);
}

Value* LgsLong::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsLong::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsLong::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsLong::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsLong::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateSRem(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsLong::bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateAnd(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsLong::bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateOr(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsLong::bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateXor(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsLong::rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateShl(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsLong::lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateLShr(self->loadIR(cg), other->loadIR(cg));
}

std::string LgsLong::getName() {
    return name;
}

bool LgsLong::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsBool::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsFloat::name) return true;
    return name == otherName;
}

std::string LgsLong::strFormatPart() const {
    return "%lu";
}
