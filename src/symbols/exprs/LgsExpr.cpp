#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsArrayExpr.h"

#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsIterator.h"

Value* LgsExpr::getIRValue(LgsModule* module) {
    if (IRValue) return IRValue;
    IRValue = createIRValue(module);
    assert(IRValue);
    return IRValue;
}

void LgsExpr::setType(LgsType* newType) {
    if (type->isUnknown()) {
        freeType(type);
    }
    type = newType;
}

LgsIterator LgsExpr::toIterator() {
    return LgsIterator(this);
}

int LgsExpr::getConstInt() {
    if (const auto intConst = asIntConst()) {
        return intConst->value;
    }
    if (const auto var = asVariable()) {
        switch (var->ref.symbolType) {
        case VAR_DEC:
            return var->ref.varDec->expr->getConstInt();
        case FIELD:
            return var->ref.field->expr->getConstInt();
        default:
            break;
        }
    }
    return -1;
}

string LgsExpr::getConstStr() {
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

void LgsExpr::free(LgsModule* module) { assert(0); }
bool LgsExpr::equals(LgsExpr* other) { assert(0); }
LgsExpr* LgsExpr::convertExpr(LgsType* toType) { assert(0); }
Value* LgsExpr::hashValue(LgsModule* module) { assert(0); }
LgsExpr* LgsExpr::clone() { assert(0); }

// Comparisons
Value* LgsExpr::subIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::mulIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::divIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::modIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::eqIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::neIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::ltIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::gtIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::geIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::leIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::andIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::orIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitAndIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitOrIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitXorIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::rshiftIR(LgsModule* module, LgsExpr* other) { assert(0); }
Value* LgsExpr::lshiftIR(LgsModule* module, LgsExpr* other) { assert(0); }

// Casting
LgsFunc* LgsExpr::asFunc() { return dynamic_cast<LgsFunc*>(this); }
LgsVariable* LgsExpr::asVariable() { return dynamic_cast<LgsVariable*>(this); }
LgsFuncCall* LgsExpr::asFuncCall() { return dynamic_cast<LgsFuncCall*>(this); }
LgsPrefixExpr* LgsExpr::asPrefixExpr() { return dynamic_cast<LgsPrefixExpr*>(this); }
LgsPostfixExpr* LgsExpr::asPostfixExpr() { return dynamic_cast<LgsPostfixExpr*>(this); }
LgsInstance* LgsExpr::asInstance() { return dynamic_cast<LgsInstance*>(this); }
LgsSelection* LgsExpr::asSelection() { return dynamic_cast<LgsSelection*>(this); }
LgsArrayExpr* LgsExpr::asArrayExpr() { return dynamic_cast<LgsArrayExpr*>(this); }
LgsHashMap* LgsExpr::asHashMap() { return dynamic_cast<LgsHashMap*>(this); }
LgsBoolConst* LgsExpr::asBoolConst() { return dynamic_cast<LgsBoolConst*>(this); }
LgsCharConst* LgsExpr::asCharConst() { return dynamic_cast<LgsCharConst*>(this); }
LgsIterIndex* LgsExpr::asIterIndex() { return dynamic_cast<LgsIterIndex*>(this); }
LgsFloatConst* LgsExpr::asFloatConst() { return dynamic_cast<LgsFloatConst*>(this); }
LgsIntConst* LgsExpr::asIntConst() { return dynamic_cast<LgsIntConst*>(this); }
LgsStrConst* LgsExpr::asStrConst() { return dynamic_cast<LgsStrConst*>(this); }
LgsTypeConst* LgsExpr::asTypeConst() { return dynamic_cast<LgsTypeConst*>(this); }
