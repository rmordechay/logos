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
#include "exprs/unary/LgsTypeExpr.h"
#include "loops/LgsLoopMetaVar.h"

class LgsTypeExpr;

Value* LgsExpr::getIRPtrTo(LgsLLVMGen& cg) const {
    const auto ty = type->getIRType(cg);
    if (IRValue->getType()->isPointerTy()) return IRValue;
    const auto ptr = cg.builder.CreateAlloca(ty);
    cg.builder.CreateStore(IRValue, ptr);
    return ptr;
}

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

bool LgsExpr::equals(const LgsExpr* other) {
    if (const auto var = asVariable()) {
        switch (var->ref.symbolType) {
        case VAR_DEC:
            return var->ref.varDec->expr == other;
        default:
            assert(0);
        }
    }
    return false;
}

void LgsExpr::completeType(LgsType* toType) {}

LgsExpr* LgsExpr::clone() {
    assert(0);
}

LgsExpr* LgsExpr::castTo(LgsType* toType) {
    assert(0);
}

Value* LgsExpr::hash(LgsLLVMGen& cg) {
    assert(0);
}

void LgsExpr::assign(LgsLLVMGen& cg, LgsExpr* expr) { assert(0); }
Value* LgsExpr::addIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::subIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::mulIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::divIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::inIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::modIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::eqIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::neIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::ltIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::gtIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::geIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::leIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::andIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::orIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitAndIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitOrIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitXorIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::rshiftIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }
Value* LgsExpr::lshiftIR(LgsLLVMGen& cg, LgsExpr* other) { assert(0); }

// Casting
LgsFunc* LgsExpr::asFunc() { return dynamic_cast<LgsFunc*>(this); }
LgsVariable* LgsExpr::asVariable() { return dynamic_cast<LgsVariable*>(this); }
LgsPrefixExpr* LgsExpr::asPrefixExpr() { return dynamic_cast<LgsPrefixExpr*>(this); }
LgsIterIndex* LgsExpr::asIterIndex() { return dynamic_cast<LgsIterIndex*>(this); }
LgsTypeExpr* LgsExpr::asTypeExpr() { return dynamic_cast<LgsTypeExpr*>(this); }
LgsInstance* LgsExpr::asInstance() { return dynamic_cast<LgsInstance*>(this); }
LgsArrayExpr* LgsExpr::asArrayExpr() { return dynamic_cast<LgsArrayExpr*>(this); }
LgsHashMap* LgsExpr::asHashMap() { return dynamic_cast<LgsHashMap*>(this); }
LgsCharConst* LgsExpr::asCharConst() { return dynamic_cast<LgsCharConst*>(this); }
LgsFloatConst* LgsExpr::asFloatConst() { return dynamic_cast<LgsFloatConst*>(this); }
LgsStrConst* LgsExpr::asStrConst() { return dynamic_cast<LgsStrConst*>(this); }
LgsVectorExpr* LgsExpr::asVectorExpr() { return dynamic_cast<LgsVectorExpr*>(this); }
LgsIntConst* LgsExpr::asIntConst() { return dynamic_cast<LgsIntConst*>(this); }
LgsLoopMetaVar* LgsExpr::asLoopMetaVar() { return dynamic_cast<LgsLoopMetaVar*>(this); }

LgsExpr::~LgsExpr() {
    if (type) {
        freeType(type);
        type = nullptr;
    }
}
