#include "types/primitives/LgsDouble.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsFloatConst.h"
#include "codegen/LgsCodeGen.h"
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
    return nullptr;
}

std::string LgsDouble::fmtStr() const {
    return "%f";
}

Type* LgsDouble::getIRType(LgsCodeGen& cg) {
    return cg.builder.getDoubleTy();
}

bool LgsDouble::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (other->asGenericType()) return true;
    if (IRName == LgsAny::name) return true;
    return false;
}

Value* LgsDouble::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), this);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsDouble::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), this);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsDouble::powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), this);
    return cg.callFunc("pow", cg.doubleTy(), {cg.doubleTy(), cg.doubleTy()}, {l, r});
}

DIType* LgsDouble::getDebugType(LgsCodeGen& cg) {
    assert(0);
}