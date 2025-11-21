#include "types/primitives/LgsInt.h"
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsSize.h"

#include <iostream>
#include <llvm/IR/DIBuilder.h>

size_t LgsInt::sizeBytes() {
    return sizeof(int);
}

Type* LgsInt::getIRType(LgsLLVMGen& cg) {
    return cg.i32Ty();
}

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(&LGS_INT, 0);
}

Lgs_TypeKind LgsInt::getRTTypeKind() {
    return RTT_INT;
}

bool LgsInt::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (other->asGeneric()) return true;
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsInt::applyBinOp(LgsType* toType, LgsBinOp& op) {
    return applyIntBinOp(toType, op.opType);
}

Value* LgsInt::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsInt::subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsInt::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsInt::divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsInt::modIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateSRem(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::powIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.callFunc("pow", cg.doubleTy(), {cg.doubleTy(), cg.doubleTy()}, {left->loadIR(cg), right->loadIR(cg)});
}

Value* LgsInt::bitAndIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateAnd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::bitOrIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateOr(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::bitXorIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateXor(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::rshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateShl(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::lshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* other) {
    return cg.builder.CreateLShr(left->loadIR(cg), other->loadIR(cg));
}

Value* LgsInt::eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpEQ(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpNE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::ltIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSLT(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::gtIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSGT(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::geIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSGE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::leIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSLE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::andIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return andInt(cg, left, right);
}

Value* LgsInt::orIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return orInt(cg, left, right);
}

std::string LgsInt::strFormatPart() const {
    return "%d";
}

std::string LgsInt::getName() {
    return name;
}

llvm::DIType* LgsInt::getDebugType(LgsLLVMGen& cg) {
    return cg.debugger.diBuilder->createBasicType(name, 32, llvm::dwarf::DW_ATE_signed);
}