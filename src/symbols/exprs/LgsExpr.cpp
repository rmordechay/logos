#include "exprs/LgsExpr.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsCast.h"
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
#include "exprs/LgsNull.h"
#include "exprs/LgsTypeExpr.h"
#include "loops/LgsLoopMetaVar.h"

LgsExpr* LgsExpr::castTo(LgsType* toType, const bool explicitCast) {
    assert(0);
}

Value* LgsExpr::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

void LgsExpr::completeType(LgsType* toType) {

}

Value* LgsExpr::hash(LgsLLVMGen& cg) {
    assert(0);
}

void LgsExpr::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    assert(0);
}

void LgsExpr::freeOwner(LgsLLVMGen& cg) {
    if (type->isHeapAlloc && owner) {
        cg.callLgsFunc("stack_removeOwner", cg.voidTy(), {cg.ptrTy()}, {owner->IRValue});
        owner = nullptr;
    }
}

int64_t LgsExpr::getConstInt() {
    if (const auto intConst = asIntConst()) {
        return intConst->value;
    }
    if (const auto var = asVariable()) {
        switch (var->ref.symbolType) {
        case VAR_DEC:
            return var->ref.varDec->expr->getConstInt();
        case FIELD:
            if (var->ref.field->expr) var->ref.field->expr->getConstInt();
            break;
        default:
            break;
        }
    }
    return -1;
}

std::string LgsExpr::getConstStr() {
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
    assert(0);
}

void LgsExpr::setType(LgsType* newType) {
    type = newType;
}


bool LgsExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsExpr* LgsExpr::clone() {
    assert(0);
}

// Casting
LgsNull* LgsExpr::asNull() { return dynamic_cast<LgsNull*>(this); }
LgsFunc* LgsExpr::asFunc() { return dynamic_cast<LgsFunc*>(this); }
LgsVariable* LgsExpr::asVariable() { return dynamic_cast<LgsVariable*>(this); }
LgsPrefixExpr* LgsExpr::asPrefixExpr() { return dynamic_cast<LgsPrefixExpr*>(this); }
LgsIterIndex* LgsExpr::asIterIndex() { return dynamic_cast<LgsIterIndex*>(this); }
LgsTypeExpr* LgsExpr::asTypeExpr() { return dynamic_cast<LgsTypeExpr*>(this); }
LgsJson* LgsExpr::asJson() { return dynamic_cast<LgsJson*>(this); }
LgsCast* LgsExpr::asCast() { return dynamic_cast<LgsCast*>(this); }
LgsInstance* LgsExpr::asInstance() { return dynamic_cast<LgsInstance*>(this); }
LgsArrayExpr* LgsExpr::asArrayExpr() { return dynamic_cast<LgsArrayExpr*>(this); }
LgsHashMap* LgsExpr::asHashMap() { return dynamic_cast<LgsHashMap*>(this); }
LgsCharConst* LgsExpr::asCharConst() { return dynamic_cast<LgsCharConst*>(this); }
LgsFloatConst* LgsExpr::asFloatConst() { return dynamic_cast<LgsFloatConst*>(this); }
LgsStrConst* LgsExpr::asStrConst() { return dynamic_cast<LgsStrConst*>(this); }
LgsVectorExpr* LgsExpr::asVectorExpr() { return dynamic_cast<LgsVectorExpr*>(this); }
LgsIntConst* LgsExpr::asIntConst() { return dynamic_cast<LgsIntConst*>(this); }
LgsLoopMetaVar* LgsExpr::asLoopMetaVar() { return dynamic_cast<LgsLoopMetaVar*>(this); }