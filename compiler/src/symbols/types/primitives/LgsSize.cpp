#include "types/primitives/LgsSize.h"

#include "LgsBinaryTokens.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

size_t LgsSize::sizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType(LgsCgModule& cg) {
    return cg.sizeTy();
}

std::string LgsSize::getName() {
    return name;
}

LgsExpr* LgsSize::getZeroValue() {
    return new LgsIntConst(this, 0);
}

LgsType* LgsSize::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!rightType->isNumber()) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MODULO: {
        if (rightType->asDouble()) return &LGS_DOUBLE;
        if (rightType->asFloat()) return &LGS_FLOAT;
        return &LGS_SIZE;
    }
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: {
        return &LGS_SIZE;
    }
    case POW: {
        return &LGS_DOUBLE;
    }
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE: {
        return &LGS_BOOL;
    }
    case NOOP:
        assert(0);
    default:
        break;
    }
    return nullptr;

}

Value* LgsSize::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsSize::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(left->loadIR(cg), r);
}

Value* LgsSize::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    auto r = right->loadIR(cg);
    if (!left->type->asVec()) {
        r = cg.builder.CreateZExt(r, getIRType(cg));
    }
    return cg.builder.CreateMul(left->loadIR(cg), r);
}

Value* LgsSize::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(left->loadIR(cg), r);
}

Value* LgsSize::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSRem(left->loadIR(cg), r);
}

Value* LgsSize::bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAnd(left->loadIR(cg), r);
}

Value* LgsSize::bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateOr(left->loadIR(cg), r);
}

Value* LgsSize::bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateXor(left->loadIR(cg), r);
}

Value* LgsSize::rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateShl(left->loadIR(cg), r);
}

Value* LgsSize::lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateLShr(left->loadIR(cg), r);
}

Constant* LgsSize::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_SIZE, cg.null());
}

bool LgsSize::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsLong::name) return true;
    return name == IRName;
}

std::string LgsSize::fmtStr() const {
    return "%zu";
}

DIType* LgsSize::getDebugType(LgsCgModule& cg) {
    assert(0);
}