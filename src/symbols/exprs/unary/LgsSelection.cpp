#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/LgsVec.h"

LgsExpr* LgsSelection::lastExpr() const {
    assert(exprs.size() > 1);
    return exprs[exprs.size() - 1];
}

LgsExpr* LgsSelection::lastExprParent() const {
    return exprs[exprs.size() - 2];
}

void LgsSelection::assign(LgsLLVM& codeGen, LgsExpr* expr) {
    const auto rIR = expr->IRValue;
    auto exprParent = lastExprParent();
    if (exprParent->type->asVec()) {
        const auto vecTy = exprParent->type->getIRType(codeGen);
        const auto vec = codeGen.builder.CreateLoad(vecTy, exprParent->IRValue);
        const auto c = lastExpr()->asVariable()->name;
        const auto i = codeGen.i32(LgsVec::getComponentIndex(c.front()));
        const auto insert = codeGen.builder.CreateInsertElement(vec, rIR, i);
        codeGen.builder.CreateStore(insert, exprParent->IRValue);
    } else {
        codeGen.builder.CreateStore(rIR, IRValue);
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

Value* LgsSelection::hash(LgsLLVM& codeGen) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hash(codeGen);
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
