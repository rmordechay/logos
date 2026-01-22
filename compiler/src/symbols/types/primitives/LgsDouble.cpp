#include "types/primitives/LgsDouble.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsFloatConst.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsAny.h"

std::string LgsDouble::getName() {
    return name;
}

size_t LgsDouble::sizeBytes() {
    return sizeof(double_t);
}

LgsExpr* LgsDouble::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

LgsType* LgsDouble::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsDouble::fmtStr() const {
    return "%f";
}

Type* LgsDouble::getIRType(LgsCgModule& cg) {
    return cg.builder.getDoubleTy();
}

Constant* LgsDouble::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), IRSize(cg), RTT_DOUBLE);
}

bool LgsDouble::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (other->asGenericType()) return true;
    if (IRName == LgsAny::name) return true;
    return false;
}

Value* LgsDouble::addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), cg.doubleTy());
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsDouble::mulIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), cg.doubleTy());
    return cg.builder.CreateFMul(l, r);
}

Value* LgsDouble::powIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), cg.doubleTy());
    return cg.callFunc("pow", cg.doubleTy(), {cg.doubleTy(), cg.doubleTy()}, {l, r});
}

DIType* LgsDouble::getDebugType(LgsCgModule& cg) {
    assert(0);
}