#include "types/primitives/LgsByte.h"
#include "codegen/LgsCgModule.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

Type* LgsByte::getIRType(LgsCgModule& cg) {
    return cg.i8Ty();
}

Constant* LgsByte::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), sizeBytes(), RTT_BYTE, cg.null());
}

LgsType* LgsByte::applyBinOp(LgsType* toType, LgsBinOp& op) {
    return applyIntBinOp(toType, op.opType);
}

Value* LgsByte::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsByte::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsByte::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsByte::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsByte::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateSRem(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsByte::bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateAnd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsByte::bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateOr(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsByte::bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateXor(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsByte::rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateShl(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsByte::lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* other) {
    return cg.builder.CreateLShr(left->loadIR(cg), other->loadIR(cg));
}

size_t LgsByte::sizeBytes() {
    return sizeof(int8_t);
}

LgsExpr* LgsByte::getZeroValue() {
    return new LgsIntConst(&LGS_BYTE, false);
}

std::string LgsByte::getName() {
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

std::string LgsByte::fmtStr() const {
    return "%d";
}

DIType* LgsByte::getDebugType(LgsCgModule& cg) {
    assert(0);
}