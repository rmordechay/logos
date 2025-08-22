#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsVectorExpr.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsIterator.h"

size_t LgsExpr::getConstInt() {
    if (const auto intConst = asIntConst()) {
        return intConst->value;
    }
    if (const auto var = asVariable()) {
        switch (var->ref.symbolType) {
        case VAR_DEC:
            return var->ref.varDec->expr->getConstInt();
        case ENUM_FIELD:
            return var->ref.field->expr->getConstInt();
        default:
            break;
        }
    }
    assert(0);
}

std::string LgsExpr::getConstStr() {
    if (const auto strConst = asStrConst()) {
        return strConst->value;
    }
    if (const auto var = asVariable()) {
        switch (var->ref.symbolType) {
        case VAR_DEC:
            return var->ref.varDec->expr->getConstStr();
        case ENUM_FIELD:
            return var->ref.field->expr->getConstStr();
        default:
            break;
        }
    }
    assert(0);
}

LgsIterator LgsExpr::toIterator() {
    return LgsIterator(this);
}

void LgsExpr::setType(LgsType* newType) {
    if (type && type->isUnknown()) freeType(type);
    type = newType;
}

bool LgsExpr::completeType(LgsType* toType) {
    return true;
}

LgsExpr* LgsExpr::clone() {
    assert(0);
}

Value* LgsExpr::hash(LgsCodeGen* codeGen) {
    assert(0);
}

// Casting
LgsFunc* LgsExpr::asFunc() { return dynamic_cast<LgsFunc*>(this); }
LgsVariable* LgsExpr::asVariable() { return dynamic_cast<LgsVariable*>(this); }
LgsPrefixExpr* LgsExpr::asPrefixExpr() { return dynamic_cast<LgsPrefixExpr*>(this); }
LgsIterIndex* LgsExpr::asIterIndex() { return dynamic_cast<LgsIterIndex*>(this); }
LgsInstance* LgsExpr::asInstance() { return dynamic_cast<LgsInstance*>(this); }
LgsArrayExpr* LgsExpr::asArrayExpr() { return dynamic_cast<LgsArrayExpr*>(this); }
LgsHashMap* LgsExpr::asHashMap() { return dynamic_cast<LgsHashMap*>(this); }
LgsCharConst* LgsExpr::asCharConst() { return dynamic_cast<LgsCharConst*>(this); }
LgsFloatConst* LgsExpr::asFloatConst() { return dynamic_cast<LgsFloatConst*>(this); }
LgsStrConst* LgsExpr::asStrConst() { return dynamic_cast<LgsStrConst*>(this); }
LgsVectorExpr* LgsExpr::asVectorExpr() { return dynamic_cast<LgsVectorExpr*>(this); }
LgsIntConst* LgsExpr::asIntConst() { return dynamic_cast<LgsIntConst*>(this); }

LgsExpr::~LgsExpr() {
    if (type) {
        freeType(type);
        type = nullptr;
    }
}
