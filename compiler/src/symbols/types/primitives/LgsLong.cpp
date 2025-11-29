#include "types/primitives/LgsLong.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"

Type* LgsLong::getIRType(LgsCgModule& cg) {
    return cg.i64Ty();
}

Constant* LgsLong::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), sizeBytes(), RTT_LONG, cg.null());
}

size_t LgsLong::sizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsIntConst(&LGS_LONG, 0);
}

LgsType* LgsLong::applyBinOp(LgsType* toType, LgsBinOp& op) {
    return applyIntBinOp(toType, op.opType);
}

Value* LgsLong::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsLong::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsLong::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsLong::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsLong::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateSRem(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsLong::bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateAnd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsLong::bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateOr(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsLong::bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateXor(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsLong::rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateShl(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsLong::lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* other) {
    return cg.builder.CreateLShr(left->loadIR(cg), other->loadIR(cg));
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

llvm::DIType* LgsLong::getDebugType(LgsCgModule& cg) {
    assert(0);
}

std::string LgsLong::strFormatPart() const {
    return "%lu";
}
