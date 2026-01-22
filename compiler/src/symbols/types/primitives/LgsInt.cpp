#include "types/primitives/LgsInt.h"
#include "LgsBinaryTokens.h"
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include <iostream>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Module.h>

#include "exprs/LgsBinaryExpr.h"

size_t LgsInt::sizeBytes() {
    return sizeof(int);
}

Type* LgsInt::getIRType(LgsCgModule& cg) {
    return cg.i32Ty();
}

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(&LGS_INT, 0);
}

Constant* LgsInt::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), IRSize(cg), RTT_INT);
}

bool LgsInt::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    return false;
}

LgsType* LgsInt::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!rightType->isNumber()) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MODULO: {
        if (rightType->asDouble()) return &LGS_DOUBLE;
        if (rightType->asFloat()) return &LGS_FLOAT;
        return &LGS_INT;
    }
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: return &LGS_INT;
    case POW: return &LGS_DOUBLE;
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE: return &LGS_BOOL;
    case NOOP:
        assert(0);
    default:
        break;
    }
    return nullptr;
}

Value* LgsInt::addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsInt::subIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsInt::mulIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsInt::divIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsInt::modIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateSRem(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::powIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.callFunc("pow", cg.doubleTy(), {cg.doubleTy(), cg.doubleTy()}, {left->loadIR(cg), right->loadIR(cg)});
}

Value* LgsInt::bitAndIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateAnd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::bitOrIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateOr(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::bitXorIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateXor(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::rshiftIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateShl(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::lshiftIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateLShr(left->loadIR(cg), right->loadIR(cg));
}

std::string LgsInt::fmtStr() const {
    return "%d";
}

std::string LgsInt::getName() {
    return name;
}

LgsType* LgsInt::clone() {
    return this;
}

DIType* LgsInt::getDebugType(LgsCgModule& cg) {
    return cg.debugger.diBuilder->createBasicType(name, 32, dwarf::DW_ATE_signed);
}
