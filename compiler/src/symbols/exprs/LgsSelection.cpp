#include "exprs/LgsSelection.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsVec.h"
#include "LgsUtils.h"
#include <sstream>
#include <llvm/IR/InlineAsm.h>

Value* LgsSelection::loadIR(LgsCgModule& cg) {
    if (type->passByRef) return cg.builder.CreateLoad(cg.ptrTy(), IRValue);
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

LgsExpr* LgsSelection::lastExpr() const {
    return exprs[exprs.size() - 1];
}

LgsFuncCall* LgsSelection::asMethodCall() const {
    return lastExpr()->asFuncCall();
}

void LgsSelection::assign(LgsCgModule& cg, LgsExpr* expr) {
    const auto rIR = expr->IRValue;
    const auto lExpr = lastExpr();
    if (lExpr->type->asVec()) {
        const auto vecTy = lExpr->type->getIRType(cg);
        const auto vec = cg.builder.CreateLoad(vecTy, lExpr->IRValue);
        const auto c = lastExpr()->asVariable()->name;
        const auto i = cg.i32(LgsVec::getComponentIndex(c.front()));
        const auto insert = cg.builder.CreateInsertElement(vec, rIR, i);
        cg.store(insert, lExpr->IRValue);
    } else {
        cg.freeValue(loadIR(cg), type->getRTType(cg));
        cg.store(rIR, IRValue);
    }
}

std::string LgsSelection::asText() {
    std::stringstream str;
    str << exprs[0]->asText();
    for (size_t i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->asText();
    }
    return str.str();
}

Value* LgsSelection::hashValue(LgsCgModule& cg) {
    return lastExpr()->hashValue(cg);
}

bool LgsSelection::equals(LgsExpr* other) {
    const auto otherSelection = other->asSelection();
    if (!otherSelection) return false;
    if (exprs.size() != otherSelection->exprs.size()) return false;
    for (size_t i = 0; i < exprs.size(); ++i) {
        const auto expr = exprs[i];
        const auto otherExpr = otherSelection->exprs[i];
        if (!expr->equals(otherExpr)) return false;
    }
    return true;
}

void LgsSelection::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsSelection::~LgsSelection() {
    freeExpr(importVar);
    importVar = nullptr;
    for (const auto& expr : exprs) {
        freeExpr(expr);
    }
    exprs.clear();
}
