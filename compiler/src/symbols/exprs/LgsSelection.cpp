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
    if (type->passByRef) return cg.load(cg.ptrTy(), IRValue);
    return cg.load(type->getIRType(cg), IRValue);
}

LgsFuncCall* LgsSelection::asMethodCall() const {
    return exprs.back()->asFuncCall();
}

void LgsSelection::assign(LgsCgModule& cg, LgsExpr* expr, Value* level) {
    assert(!type->asVec());
    if (type->isHeapAlloc) {
        cg.moveAlloc(level, cg.sizeZero(), loadIR(cg), expr->IRValue);
    }
    cg.store(expr->IRValue, IRValue);
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
    return exprs.back()->hashValue(cg);
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
