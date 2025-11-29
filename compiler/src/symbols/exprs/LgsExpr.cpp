#include "exprs/LgsExpr.h"
#include "exprs/LgsArrayExpr.h"
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
#include "exprs/LgsNull.h"
#include "exprs/LgsNullableExpr.h"
#include "exprs/LgsTypeExpr.h"
#include "funcs/LgsFunc.h"
#include "loops/LgsMetaVar.h"

LgsExpr* LgsExpr::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsExpr::castImplicitly(LgsType* toType) {

}

Value* LgsExpr::castIR(LgsCgModule& cg, LgsType* toType) {
    assert(0);
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

void LgsExpr::freeOwner(LgsCgModule& cg) {
    if (type->isHeapAlloc && owner) {
        cg.callRuntimeFunc("removeOwner", cg.voidTy(), {cg.ptrTy()}, {owner->IRValue});
        owner = nullptr;
    }
}

int64_t* LgsExpr::getConstInt() {
    if (const auto intConst = asIntConst()) {
        return &intConst->value;
    }
    if (const auto var = asVariable()) {
        if (var->isMutable) return nullptr;
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
        if (binExpr->isMutable) return nullptr;
        if (binExpr->results) return binExpr->results->getConstInt();
        const auto const1 = binExpr->left->getConstInt();
        if (!const1) return nullptr;
        const auto const2 = binExpr->right->getConstInt();
        if (!const2) return nullptr;
        const auto malloc = static_cast<int64_t*>(std::malloc(sizeof(int64_t)));
        *malloc = *const1 + *const2;
        return malloc;
    }
    return nullptr;
}

std::string* LgsExpr::getConstStr() {
    if (const auto strConst = asStrConst()) {
        return &strConst->value;
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
    if (const auto bin = asBinExpr()) {
        if (bin->op.opType == ADD) {
            return &bin->results->asStrConst()->value;
        }
    }
    return nullptr;
}

void LgsExpr::setType(LgsType* newType) {
    type = newType;
}


// Casting
LgsNull* LgsExpr::asNull() {
    return dynamic_cast<LgsNull*>(this);
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

LgsNullableExpr* LgsExpr::asNullableExpr() {
    return dynamic_cast<LgsNullableExpr*>(this);
}

LgsMetaSelection* LgsExpr::asMetaSelection() {
    return dynamic_cast<LgsMetaSelection*>(this);
}

void freeExpr(LgsExpr* expr) {
    if (!expr) return;
    expr->setType(nullptr);
    delete expr;
}

void freeExprs(std::vector<LgsExpr*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(expr);
    }
    exprs.clear();
}
