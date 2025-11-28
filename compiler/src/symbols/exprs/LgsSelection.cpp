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
    assert(0);
}

LgsExpr* LgsSelection::lastExpr() const {
    return exprs[exprs.size() - 1];
}

LgsFuncCall* LgsSelection::asMethodCall() const {
    return lastExpr()->asFuncCall();
}

Value* LgsSelection::castIR(LgsCgModule& cg, LgsType* toType) {
    return IRValue;
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
        cg.builder.CreateStore(insert, lExpr->IRValue);
    } else {
        freeOwner(cg);
        if (const auto gv = llvm::dyn_cast<GlobalVariable>(rIR)) {
            assert(0);
        } else {
            cg.builder.CreateStore(rIR, IRValue);
        }
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

LgsSelection::~LgsSelection() {
    freeExpr(importVar);
    importVar = nullptr;
    for (const auto& expr : exprs) {
        freeExpr(expr);
    }
    exprs.clear();
}
