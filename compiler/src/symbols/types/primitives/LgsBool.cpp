#include "types/primitives/LgsBool.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
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

LgsType* LgsBool::applyBinOp(LgsBinaryExpr* binExpr) {
    return applyIntBinOp(binExpr->op.opType, binExpr->left->type);
}

LgsExpr* LgsBool::addConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 + *const2);
}

LgsExpr* LgsBool::subConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 - *const2);
}

LgsExpr* LgsBool::mulConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 * *const2);
}

LgsExpr* LgsBool::divConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 / *const2);
}

LgsExpr* LgsBool::modConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 % *const2);
}

LgsExpr* LgsBool::bitAndConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 & *const2);
}

LgsExpr* LgsBool::bitOrConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 | *const2);
}

LgsExpr* LgsBool::bitXorConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 ^ *const2);
}

LgsExpr* LgsBool::lshiftConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 << *const2);
}

LgsExpr* LgsBool::rshiftConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 >> *const2);
}

LgsExpr* LgsBool::eqConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 == *const2);
}

LgsExpr* LgsBool::neConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 != *const2);
}

LgsExpr* LgsBool::ltConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 < *const2);
}

LgsExpr* LgsBool::gtConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 > *const2);
}

LgsExpr* LgsBool::geConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 >= *const2);
}

LgsExpr* LgsBool::leConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 <= *const2);
}

LgsExpr* LgsBool::andConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 > 0 && *const2 > 0);
}

LgsExpr* LgsBool::orConst(LgsExpr* left, LgsExpr* right) {
    const auto const1 = left->getConstInt();
    if (!const1) return nullptr;
    const auto const2 = right->getConstInt();
    if (!const2) return nullptr;
    return new LgsIntConst(&LGS_BOOL, *const1 > 0 || *const2 > 0);
}

Value* LgsBool::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsBool::subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsBool::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsBool::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto l = cg.builder.CreateZExt(self->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(other->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsBool::modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateSRem(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateAnd(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateOr(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateXor(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateShl(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    return cg.builder.CreateLShr(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpEQ(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpNE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::ltIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSLT(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::gtIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSGT(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::geIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSGE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::leIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSLE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::andIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return andInt(cg, left, right);
}

Value* LgsBool::orIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return orInt(cg, left, right);
}

std::string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

Lgs_TypeKind LgsBool::getRTTypeKind() {
    return RTT_BOOL;
}

std::string LgsBool::strFormatPart() const {
    return "%s";
}

size_t LgsBool::sizeBytes() {
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
