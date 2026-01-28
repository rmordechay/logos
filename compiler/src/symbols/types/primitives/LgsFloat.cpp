#include "types/primitives/LgsFloat.h"

#include <llvm/IR/Module.h>

#include "LgsBinaryTokens.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"

std::string LgsFloat::getName() {
    return name;
}

Type* LgsFloat::getIRType(LgsCodeGen& cg) {
    return Type::getFloatTy(cg.context);
}

LgsExpr* LgsFloat::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

Constant* LgsFloat::getRTType(LgsCodeGen& cg) {
    return cg.getRTTypeInfo(getName(), IRSize(cg), RTT_FLOAT);
}

size_t LgsFloat::sizeBytes() {
    return sizeof(float);
}

std::string LgsFloat::fmtStr() const {
    return "%.3f";
}

Value* LgsFloat::asIRStr(LgsCodeGen& cg, Value* v) {
    return cg.callSnprintf(fmtStr(), {cg.builder.CreateFPExt(v, cg.doubleTy())});
}

bool LgsFloat::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (name == IRName) return true;
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsFloat::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!rightType->isNumber()) return nullptr;
    switch (op.opType) {
    case POW:
        return &LGS_DOUBLE;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MODULO:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT:
        if (rightType->asDouble()) return &LGS_DOUBLE;
        return &LGS_FLOAT;
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE:
        return &LGS_BOOL;
    case AND:
    case OR:
    case IN:
    case CROSS:
        break;
    case NOOP:
        assert(0);
    }
    return nullptr;
}

Value* LgsFloat::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), cg.floatTy());
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), cg.floatTy());
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    if (left->type->asVec() && right->type->asVec()) {
        const auto dotFunc = dotProductFunc(cg, left->type->asVec());
        return cg.builder.CreateCall(dotFunc, {left->loadIR(cg), right->loadIR(cg)});
    }
    auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), cg.floatTy());
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    auto [l, r] = loadNumberPair(cg, left->loadIR(cg), right->loadIR(cg), cg.floatTy());
    return cg.builder.CreateFDiv(l, r);
}

DIType* LgsFloat::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsType* LgsFloat::clone() {
    return this;
}
