#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

LgsExpr* LgsSelection::lastExpr() const {
    assert(exprs.size() > 1);
    return exprs[exprs.size() - 1];
}

LgsExpr* LgsSelection::lastExprParent() const {
    return exprs[exprs.size() - 2];
}

std::string LgsSelection::pname() {
    std::stringstream str;
    str << exprs[0]->pname();
    for (int i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->pname();
    }
    return str.str();
}

Value* LgsSelection::hash(LgsCodeGen& codeGen) {
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
