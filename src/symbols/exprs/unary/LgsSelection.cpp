#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsVec.h"

Value* LgsSelection::loadIR(LgsLLVMGen& cg) {
    return lastExpr()->loadIR(cg);
}

LgsExpr* LgsSelection::lastExpr() const {
    assert(exprs.size() > 1);
    return exprs[exprs.size() - 1];
}

LgsExpr* LgsSelection::lastExprParent() const {
    return exprs[exprs.size() - 2];
}

void LgsSelection::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    const auto rIR = expr->IRValue;
    const auto exprParent = lastExprParent();
    if (exprParent->type->asVec()) {
        const auto vecTy = exprParent->type->getIRType(cg);
        const auto vec = cg.builder.CreateLoad(vecTy, exprParent->IRValue);
        const auto c = lastExpr()->asVariable()->name;
        const auto i = cg.i32(LgsVec::getComponentIndex(c.front()));
        const auto insert = cg.builder.CreateInsertElement(vec, rIR, i);
        cg.builder.CreateStore(insert, exprParent->IRValue);
    } else {
        cg.builder.CreateStore(rIR, IRValue);
    }
}

std::string LgsSelection::pname() {
    std::stringstream str;
    str << exprs[0]->pname();
    for (int i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->pname();
    }
    return str.str();
}

LgsExpr* LgsSelection::castTo(LgsType* toType) {
    if (type->getName() == toType->getName()) return this;
    assert(0);
}

Value* LgsSelection::hash(LgsLLVMGen& cg) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hash(cg);
}

json::value LgsSelection::asJSON() {
    json::object jsonObj;
    jsonObj["stmtKind"] = "selection";
    json::array exprParts;
    for (const auto& expr : exprs) {
        exprParts.emplace_back(expr->asJSON());
    }
    jsonObj["parts"] = exprParts;
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        // TODO delete
        // freeExpr(expr);
    }
    exprs.clear();
}
