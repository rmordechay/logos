#include "types/primitives/LgsFloat.h"

#include <llvm/IR/Module.h>

#include "LgsBinaryTokens.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/constants/LgsFloatConst.h"
#include "../../../../include/symbols/types/primitives/LgsAny.h"
#include "types/LgsNullable.h"
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

Value* LgsFloat::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.floatv(0);
}

Value* LgsFloat::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.toSize(cg.builder.CreateBitCast(value, cg.i32Ty()));
}

size_t LgsFloat::sizeBytes() {
    return sizeof(float);
}

std::string LgsFloat::fmtStr() const {
    return "%.3f";
}

bool LgsFloat::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (other->isAny()) return true;
    if (otherName == LgsDouble::name) return true;
    if (other->asGenericType()) return other->canCastTo(this);
    if (const auto nullable = other->asNullable()) return canCastTo(nullable->baseType);
    return false;
}

void LgsFloat::asIRText(LgsCodeGen& cg, LgsStrBuilder& strBuilder, Value* ptr) {
    const auto buffer = cg.emptyBuffer(128);
    const auto bytesRead = cg.callSnprintf(fmtStr(), buffer, cg.usize(128), ptr);
    strBuilder.add(buffer, cg.toSize(bytesRead));
}

LgsType* LgsFloat::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!rightType->isScalar()) return nullptr;
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
    auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    if (left->type->asVec() && right->type->asVec()) {
        const auto dotFunc = getDotProductFunc(cg, left->type->asVec());
        return cg.builder.CreateCall(dotFunc, {left->IRValue, right->IRValue});
    }
    auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    auto [l, r] = loadNumberPair(cg, left->IRValue, right->IRValue, this);
    return cg.builder.CreateFDiv(l, r);
}

DIType* LgsFloat::getDebugType(LgsCodeGen& cg) {
    assert(0);
}