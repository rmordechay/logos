#include "exprs/LgsExpr.h"

#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsEnvVar.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsCharConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "exprs/LgsMatrixExpr.h"
#include "exprs/LgsMetaSelection.h"
#include "exprs/LgsModuleExpr.h"
#include "exprs/LgsNullableExpr.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTypeExpr.h"
#include "funcs/LgsFunc.h"
#include "loops/LgsMetaVar.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsNullable.h"

LgsType* LgsExpr::getType() {
    return type;
}

void LgsExpr::setType(LgsType* newType) {
    type = newType;
}

std::optional<int64_t> LgsExpr::getConstInt() {
    if (const auto intConst = asIntConst()) {
        return intConst->value;
    }
    if (const auto var = asVariable()) {
        if (var->ref.symbolType == VAR_DEC) {
            if (var->ref.varDec->isMutable) return std::nullopt;
            return var->ref.varDec->expr->getConstInt();
        }
    }
    if (const auto binExpr = asBinExpr()) {
        const auto const1 = binExpr->left->getConstInt();
        if (!const1.has_value()) return std::nullopt;
        const auto const2 = binExpr->right->getConstInt();
        if (!const2.has_value()) return std::nullopt;

        switch (binExpr->op.opType) {
        case ADD: return const1.value() + const2.value();
        case SUB: return const1.value() - const2.value();
        case MUL: return const1.value() * const2.value();
        case DIV: return const1.value() / const2.value();
        case MODULO: return const1.value() % const2.value();
        case POW: return std::pow(const1.value(), const2.value());
        case BIT_AND: return const1.value() & const2.value();
        case BIT_OR: return const1.value() | const2.value();
        case BIT_XOR: return const1.value() ^ const2.value();
        case LSHIFT: return const1.value() << const2.value();
        case RSHIFT: return const1.value() >> const2.value();
        default: break;
        }
    }
    return std::nullopt;
}

std::optional<double_t> LgsExpr::getConstFloat() {
    if (const auto intConst = asIntConst()) {
        return intConst->value;
    }
    if (const auto floatConst = asFloatConst()) {
        return floatConst->value;
    }
    if (const auto var = asVariable()) {
        if (var->ref.symbolType == VAR_DEC) {
            if (var->ref.varDec->isMutable) return std::nullopt;
            return var->ref.varDec->expr->getConstFloat();
        }
    }
    if (const auto binExpr = asBinExpr()) {
        const auto const1 = binExpr->left->getConstFloat();
        if (!const1.has_value()) return std::nullopt;
        const auto const2 = binExpr->right->getConstFloat();
        if (!const2.has_value()) return std::nullopt;

        switch (binExpr->op.opType) {
        case ADD: return const1.value() + const2.value();
        case SUB: return const1.value() - const2.value();
        case MUL: return const1.value() * const2.value();
        case DIV: return const1.value() / const2.value();
        default: break;
        }
    }
    return std::nullopt;
}

std::optional<std::string> LgsExpr::getConstStr() {
    if (const auto strConst = asStrConst()) {
        return strConst->value;
    }
    if (const auto charConst = asCharConst()) {
        return std::to_string(charConst->value - '0');
    }
    if (const auto var = asVariable()) {
        if (var->ref.symbolType == VAR_DEC) {
            if (var->ref.varDec->isMutable) return std::nullopt;
            return var->ref.varDec->expr->getConstStr();
        }
    }
    if (const auto binExpr = asBinExpr()) {
        const auto const1 = binExpr->left->getConstStr();
        if (!const1.has_value()) return std::nullopt;
        if (binExpr->right->type->asStr()) {
            const auto const2 = binExpr->right->getConstStr();
            if (!const2.has_value()) return std::nullopt;
            return const1.value() + const2.value();
        }
        if (binExpr->right->type->isInt) {
            const auto const2 = binExpr->right->getConstInt();
            if (!const2.has_value()) return std::nullopt;
            return const1.value() + std::to_string(const2.value());
        }
        if (binExpr->right->type->isFloat) {
            const auto const2 = binExpr->right->getConstFloat();
            if (!const2.has_value()) return std::nullopt;
            return const1.value() + std::to_string(const2.value());
        }
    }
    return std::nullopt;
}

Value* LgsExpr::loadIRPtr(LgsCodeGen& cg) const {
    if (!IRValue->getType()->isPointerTy()) return IRValue;
    if (type->asSArray()) return IRValue;
    if (type->asNullable() && !type->passByRef) return IRValue;
    return cg.load(type->getTypeOrPtr(cg), IRValue);
}

LgsExpr* LgsExpr::cast(LgsType* toType, const bool explicitly) {
    return this;
}

bool LgsExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsFunc* LgsExpr::asFunc() {
    return dynamic_cast<LgsFunc*>(this);
}

LgsCast* LgsExpr::asCast() {
    return dynamic_cast<LgsCast*>(this);
}

LgsVariable* LgsExpr::asVariable() {
    return dynamic_cast<LgsVariable*>(this);
}

LgsModuleExpr* LgsExpr::asModuleExpr() {
    return dynamic_cast<LgsModuleExpr*>(this);
}

LgsPrefixExpr* LgsExpr::asPrefixExpr() {
    return dynamic_cast<LgsPrefixExpr*>(this);
}

LgsFuncCall* LgsExpr::asFuncCall() {
    return dynamic_cast<LgsFuncCall*>(this);
}

LgsPostfixExpr* LgsExpr::asPostfixExpr() {
    return dynamic_cast<LgsPostfixExpr*>(this);
}

LgsSelection* LgsExpr::asSelection() {
    return dynamic_cast<LgsSelection*>(this);
}

LgsIterIndex* LgsExpr::asIterIndex() {
    return dynamic_cast<LgsIterIndex*>(this);
}

LgsTypeExpr* LgsExpr::asTypeExpr() {
    return dynamic_cast<LgsTypeExpr*>(this);
}

LgsInstance* LgsExpr::asInstance() {
    return dynamic_cast<LgsInstance*>(this);
}

LgsArrayExpr* LgsExpr::asArrayExpr() {
    return dynamic_cast<LgsArrayExpr*>(this);
}

LgsHashMap* LgsExpr::asHashMap() {
    return dynamic_cast<LgsHashMap*>(this);
}

LgsPair* LgsExpr::asPair() {
    return dynamic_cast<LgsPair*>(this);
}

LgsEnvVar* LgsExpr::asEnvVar() {
    return dynamic_cast<LgsEnvVar*>(this);
}

LgsIntConst* LgsExpr::asIntConst() {
    return dynamic_cast<LgsIntConst*>(this);
}

LgsStrConst* LgsExpr::asStrConst() {
    return dynamic_cast<LgsStrConst*>(this);
}

LgsCharConst* LgsExpr::asCharConst() {
    return dynamic_cast<LgsCharConst*>(this);
}

LgsFloatConst* LgsExpr::asFloatConst() {
    return dynamic_cast<LgsFloatConst*>(this);
}

LgsVectorExpr* LgsExpr::asVectorExpr() {
    return dynamic_cast<LgsVectorExpr*>(this);
}

LgsMatrixExpr* LgsExpr::asMatrixExpr() {
    return dynamic_cast<LgsMatrixExpr*>(this);
}

LgsMetaVar* LgsExpr::asLoopMetaVar() {
    return dynamic_cast<LgsMetaVar*>(this);
}

LgsBinaryExpr* LgsExpr::asBinExpr() {
    return dynamic_cast<LgsBinaryExpr*>(this);
}

LgsMetaVar* LgsExpr::asMetaVar() {
    return dynamic_cast<LgsMetaVar*>(this);
}

LgsMetaSelection* LgsExpr::asMetaSelection() {
    return dynamic_cast<LgsMetaSelection*>(this);
}

LgsNullableExpr* LgsExpr::asNullableExpr() {
    return dynamic_cast<LgsNullableExpr*>(this);
}

LgsExpr* LgsExpr::clone() {
    assert(0);
}

void castExprImplicitly(LgsExpr*& expr, LgsType* toType) {
    expr = expr->cast(toType, false);
    if (!expr->type->asNullable() && toType->asNullable()) {
        expr = new LgsNullableExpr(expr);
    }
}

void freeExpr(LgsExpr* expr) {
    if (!expr) return;
    expr->setType(nullptr);
    delete expr;
}
