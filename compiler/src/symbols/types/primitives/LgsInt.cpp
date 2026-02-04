#include "types/primitives/LgsInt.h"
#include "LgsBinaryTokens.h"
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include <iostream>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Module.h>
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsNullable.h"

std::string LgsInt::getName() {
    return name;
}

size_t LgsInt::sizeBytes() {
    return sizeof(int);
}

std::string LgsInt::fmtStr() const {
    return "%d";
}

bool LgsInt::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (other->isAny()) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    if (const auto nullable = other->asNullable()) return canCastTo(nullable->baseType);
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

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(&LGS_INT, 0);
}

Value* LgsInt::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.zero32();
}

Type* LgsInt::getIRType(LgsCodeGen& cg) {
    return cg.i32Ty();
}

Value* LgsInt::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateAdd(l, r);
}

Value* LgsInt::subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSub(l, r);
}

Value* LgsInt::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateMul(l, r);
}

Value* LgsInt::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.builder.CreateZExt(left->loadIR(cg), getIRType(cg));
    const auto r = cg.builder.CreateZExt(right->loadIR(cg), getIRType(cg));
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsInt::modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateSRem(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.callFunc("pow", cg.doubleTy(), {cg.doubleTy(), cg.doubleTy()}, {left->loadIR(cg), right->loadIR(cg)});
}

Value* LgsInt::bitAndIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateAnd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::bitOrIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateOr(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::bitXorIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateXor(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::rshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateShl(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsInt::lshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    return cg.builder.CreateLShr(left->loadIR(cg), right->loadIR(cg));
}

DIType* LgsInt::getDebugType(LgsCodeGen& cg) {
    return cg.debugger.diBuilder->createBasicType(name, 32, dwarf::DW_ATE_signed);
}
