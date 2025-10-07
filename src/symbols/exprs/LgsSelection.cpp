#include "exprs/LgsSelection.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsVec.h"

Value* LgsSelection::loadIR(LgsLLVMGen& cg) {
    assert(0);
}

LgsExpr* LgsSelection::lastExpr() const {
    return exprs[exprs.size() - 1];
}

LgsFuncCall* LgsSelection::asMethodCall() const {
    return lastExpr()->asFuncCall();
}

void LgsSelection::assign(LgsLLVMGen& cg, LgsExpr* expr) {
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
        cg.builder.CreateStore(rIR, IRValue);
    }
}

std::string LgsSelection::getName() {
    std::stringstream str;
    str << exprs[0]->getName();
    for (int i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->getName();
    }
    return str.str();
}

Value* LgsSelection::hash(LgsLLVMGen& cg) {
    assert(0);
}

bool LgsSelection::equals(LgsExpr* other) {
    const auto otherSelection = other->asSelection();
    if (!otherSelection) return false;
    if (exprs.size() != otherSelection->exprs.size()) return false;
    for (int i = 0; i < exprs.size(); ++i) {
        const auto expr = exprs[i];
        const auto otherExpr = otherSelection->exprs[i];
        if (!expr->equals(otherExpr)) return false;
    }
    return true;
}

void LgsSelection::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "kind", "Selection", true);
    openJsonKeyArray(json, "exprs");
    bool first = true;
    for (const auto& expr : exprs) {
        if (!first) json << ',';
        first = false;
        expr->parseAsJSON(json);
    }
    closeJsonArray(json);
    closeJsonObject(json);
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        // TODO delete
        // freeExpr(expr);
    }
    exprs.clear();
}
