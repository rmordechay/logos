#include "exprs/LgsSelection.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsVec.h"
#include "LgsUtils.h"
#include <sstream>
#include <llvm/IR/InlineAsm.h>

Value* LgsSelection::loadIR(LgsCodeGen& cg) {
    if (type->asEnum()) return IRValue;
    if (!type->passByRef && asMethodCall()) return IRValue;
    return cg.load(type->getTypeOrPtr(cg), IRValue);
}

LgsFuncCall* LgsSelection::asMethodCall() const {
    return exprs.back()->asFuncCall();
}

std::string LgsSelection::asText() {
    std::stringstream str;
    str << exprs[0]->asText();
    for (size_t i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->asText();
    }
    return str.str();
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

void LgsSelection::setDebugValue(LgsCodeGen& cg) {
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
