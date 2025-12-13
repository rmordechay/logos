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
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "exprs/LgsJson.h"
#include "exprs/LgsMatrixExpr.h"
#include "exprs/LgsMetaSelection.h"
#include "exprs/LgsNullableExpr.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTypeExpr.h"
#include "funcs/LgsFunc.h"
#include "loops/LgsMetaVar.h"

std::optional<int64_t> LgsExpr::getConstInt() {
    if (const auto intConst = asIntConst()) {
        return intConst->value;
    }
    if (const auto var = asVariable()) {
        if (var->isMutable) return std::nullopt;
        switch (var->ref.symbolType) {
        case VAR_DEC:
            return var->ref.varDec->expr->getConstInt();
        case FIELD:
            if (var->ref.field->expr) return var->ref.field->expr->getConstInt();
            break;
        default:
            break;
        }
    }
    if (const auto binExpr = asBinExpr()) {
        if (binExpr->isMutable) return std::nullopt;
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

std::optional<std::string> LgsExpr::getConstStr() {
    if (const auto strConst = asStrConst()) {
        return strConst->value;
    }
    if (const auto var = asVariable()) {
        switch (var->ref.symbolType) {
        case VAR_DEC:
            return var->ref.varDec->expr->getConstStr();
        case FIELD:
            return var->ref.field->expr->getConstStr();
        default:
            break;
        }
    }
    return std::nullopt;
}

void LgsExpr::setType(LgsType* newType) {
    type = newType;
}

LgsExpr* LgsExpr::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsExpr::castImplicitly(LgsType* toType) {

}

Value* LgsExpr::hashValue(LgsCgModule& cg) {
    assert(0);
}

void LgsExpr::assign(LgsCgModule& cg, LgsExpr* expr) {
    assert(0);
}

bool LgsExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsExpr* LgsExpr::clone() {
    assert(0);
}

LgsFunc* LgsExpr::asFunc() {
    return dynamic_cast<LgsFunc*>(this);
}

LgsVariable* LgsExpr::asVariable() {
    return dynamic_cast<LgsVariable*>(this);
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

LgsJson* LgsExpr::asJson() {
    return dynamic_cast<LgsJson*>(this);
}

LgsCast* LgsExpr::asCast() {
    return dynamic_cast<LgsCast*>(this);
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

LgsEnvVar* LgsExpr::asEnvVar() {
    return dynamic_cast<LgsEnvVar*>(this);
}

LgsCharConst* LgsExpr::asCharConst() {
    return dynamic_cast<LgsCharConst*>(this);
}

LgsFloatConst* LgsExpr::asFloatConst() {
    return dynamic_cast<LgsFloatConst*>(this);
}

LgsStrConst* LgsExpr::asStrConst() {
    return dynamic_cast<LgsStrConst*>(this);
}

LgsVectorExpr* LgsExpr::asVectorExpr() {
    return dynamic_cast<LgsVectorExpr*>(this);
}

LgsMatrixExpr* LgsExpr::asMatrixExpr() {
    return dynamic_cast<LgsMatrixExpr*>(this);
}

LgsIntConst* LgsExpr::asIntConst() {
    return dynamic_cast<LgsIntConst*>(this);
}

LgsMetaVar* LgsExpr::asLoopMetaVar() {
    return dynamic_cast<LgsMetaVar*>(this);
}

LgsBinaryExpr* LgsExpr::asBinExpr() {
    return dynamic_cast<LgsBinaryExpr*>(this);
}

LgsMetaSelection* LgsExpr::asMetaSelection() {
    return dynamic_cast<LgsMetaSelection*>(this);
}

LgsNullableExpr* LgsExpr::asNullableExpr() {
    return dynamic_cast<LgsNullableExpr*>(this);
}

Value* dotProduct(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = left->loadIR(cg);
    const auto r = right->loadIR(cg);

    const auto lx = cg.builder.CreateExtractElement(l, cg.i32(0));
    const auto rx = cg.builder.CreateExtractElement(r, cg.i32(0));
    const auto ly = cg.builder.CreateExtractElement(l, cg.i32(1));
    const auto ry = cg.builder.CreateExtractElement(r, cg.i32(1));
    const auto mulX = cg.builder.CreateFMul(lx, rx);
    const auto mulY = cg.builder.CreateFMul(ly, ry);
    Value* result = cg.builder.CreateFAdd(mulX, mulY);

    const auto vectorDim = left->type->asVec()->vectorDim;
    if (vectorDim == 3) {
        const auto lz = cg.builder.CreateExtractElement(l, cg.i32(2));
        const auto rz = cg.builder.CreateExtractElement(r, cg.i32(2));
        const auto mulZ = cg.builder.CreateFMul(lz, rz);
        result = cg.builder.CreateFAdd(result, mulZ);
    } else if (vectorDim == 4) {
        const auto lw = cg.builder.CreateExtractElement(l, cg.i32(3));
        const auto rw = cg.builder.CreateExtractElement(r, cg.i32(3));
        const auto mulW = cg.builder.CreateFMul(lw, rw);
        result = cg.builder.CreateFAdd(result, mulW);
    }
    return result;
}

Value* crossProduct(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = left->loadIR(cg);
    const auto r = right->loadIR(cg);

    const auto lx = cg.builder.CreateExtractElement(l, cg.i32(0));
    const auto ly = cg.builder.CreateExtractElement(l, cg.i32(1));
    const auto lz = cg.builder.CreateExtractElement(l, cg.i32(2));
    const auto rx = cg.builder.CreateExtractElement(r, cg.i32(0));
    const auto ry = cg.builder.CreateExtractElement(r, cg.i32(1));
    const auto rz = cg.builder.CreateExtractElement(r, cg.i32(2));

    const auto cx = cg.builder.CreateFSub(
        cg.builder.CreateFMul(ly, rz),
        cg.builder.CreateFMul(lz, ry)
    );
    const auto cy = cg.builder.CreateFSub(
        cg.builder.CreateFMul(lz, rx),
        cg.builder.CreateFMul(lx, rz)
    );
    const auto cz = cg.builder.CreateFSub(
        cg.builder.CreateFMul(lx, ry),
        cg.builder.CreateFMul(ly, rx)
    );

    const auto vecTy = left->type->getIRType(cg);
    Value* result = UndefValue::get(vecTy);
    result = cg.builder.CreateInsertElement(result, cx, cg.i32(0));
    result = cg.builder.CreateInsertElement(result, cy, cg.i32(1));
    result = cg.builder.CreateInsertElement(result, cz, cg.i32(2));

    return result;
}

void castExprImplicitly(LgsExpr*& expr, LgsType* toType) {
    expr->castImplicitly(toType);
    if (!expr->asVariable() && !expr->asNullableExpr() && toType->asNullable()) {
        // The Expr and its type are wrapped in NullableExpr and Nullable.
        const auto& nullable = toType->asNullable();
        expr->type = nullable->baseType;
        expr = new LgsNullableExpr(expr);
        expr->type = nullable;
    }
}

void freeExpr(LgsExpr* expr) {
    if (!expr) return;
    expr->setType(nullptr);
    delete expr;
}
