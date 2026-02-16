#include "types/primitives/LgsDouble.h"

#include <llvm/IR/Module.h>

#include "exprs/constants/LgsFloatConst.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsBinaryExpr.h"
#include "../../../../include/symbols/types/primitives/LgsAny.h"
#include "types/primitives/LgsBool.h"

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
    if (!rightType->isScalar()) return nullptr;
    switch (op.opType) {
    case POW:
        return &LGS_DOUBLE;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
        if (rightType->isScalar()) return this;
        return nullptr;
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE:
        return &LGS_BOOL;
    default:
        break;
    }
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
    const auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsDouble::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsDouble::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.builder.CreateFDiv(l, r);
}

Value* LgsDouble::powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.callFunc("pow", cg.doubleTy(), {cg.doubleTy(), cg.doubleTy()}, {l, r});
}

DIType* LgsDouble::getDebugType(LgsCodeGen& cg) {
    assert(0);
}