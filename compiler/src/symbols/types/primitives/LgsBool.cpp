#include "types/primitives/LgsBool.h"

#include "exprs/LgsNullableExpr.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

Type* LgsBool::getIRType(LgsCgModule& cg) {
    return cg.i1Ty();
}

Constant* LgsBool::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), sizeBytes(), RTT_BOOL, cg.null());
}

LgsType* LgsBool::applyBinOp(LgsType* toType, LgsBinOp& op) {
    return applyIntBinOp(toType, op.opType);
}

Value* LgsBool::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

// BinExpr type
// left expr
// left type
// right expr
// right type

// Value* LgsExpr::subIR(LgsCgModule& cg, LgsExpr* right) {
// Value* LgsType::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
// Value* LgsBinExpr::subIR(LgsCgModule& cg) {

Value* LgsBool::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsBool::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsBool::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsBool::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateSRem(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateAnd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateOr(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateXor(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateShl(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* other) {
    return cg.builder.CreateLShr(left->loadIR(cg), other->loadIR(cg));
}

Value* LgsBool::eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto f = [&cg](const LgsExpr* expr) {
        if (expr->type->asNullable()->passByRef) return cg.builder.CreateIsNull(expr->IRValue);
        const auto gepIsSet = cg.builder.CreateStructGEP(expr->type->getIRType(cg), expr->IRValue, 1);
        return cg.builder.CreateNot(cg.builder.CreateLoad(cg.i1Ty(), gepIsSet));
    };
    if (left->isNull && right->isNull) return cg.true_();
    if (left->isNull) return f(right);
    if (right->isNull) return f(left);
    return cg.builder.CreateICmpEQ(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::neIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto f = [&cg](const LgsExpr* expr) -> Value* {
        if (expr->type->asNullable()->passByRef) return cg.builder.CreateIsNotNull(expr->IRValue);
        const auto gepIsSet = cg.builder.CreateStructGEP(expr->type->getIRType(cg), expr->IRValue, 1);
        return cg.builder.CreateLoad(cg.i1Ty(), gepIsSet);
    };
    if (left->isNull && right->isNull) return cg.false_();
    if (left->isNull) return f(right);
    if (right->isNull) return f(left);
    return cg.builder.CreateICmpNE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::ltIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSLT(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::gtIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSGT(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::geIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSGE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::leIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return cg.builder.CreateICmpSLE(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsBool::andIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return andInt(cg, left->IRValue, right->IRValue);
}

Value* LgsBool::orIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    return orInt(cg, left->IRValue, right->IRValue);
}

std::string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

std::string LgsBool::fmtStr() const {
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

DIType* LgsBool::getDebugType(LgsCgModule& cg) {
    assert(0);
}