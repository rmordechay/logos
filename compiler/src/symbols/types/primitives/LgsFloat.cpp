#include "types/primitives/LgsFloat.h"

#include "LgsBinaryTokens.h"
#include "codegen/LgsCgModule.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsIterable.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"

std::string LgsFloat::getName() {
    return name;
}

Type* LgsFloat::getIRType(LgsCgModule& cg) {
    return Type::getFloatTy(cg.context);
}

LgsExpr* LgsFloat::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

Constant* LgsFloat::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_FLOAT, cg.i1(isHeapAlloc), cg.null());
}

size_t LgsFloat::sizeBytes() {
    return sizeof(float);
}

std::string LgsFloat::fmtStr() const {
    return "%.3f";
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

Value* LgsFloat::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloat::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloat::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->asVec() && right->type->asVec()) {
        return dotProduct(cg, left, right);
    }
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloat::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto [l, r] = loadPairAsFloat(cg, left, right);
    return cg.builder.CreateFDiv(l, r);
}

DIType* LgsFloat::getDebugType(LgsCgModule& cg) {
    assert(0);
}