#include "exprs/LgsSelection.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsVec.h"

Value* LgsSelection::loadIR(LgsLLVMGen& cg) {
    const auto gep = lastExprParent()->loadIR(cg);
    return cg.builder.CreateLoad(type->getIRType(cg), gep);
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
    const auto lExpr = lastExpr();
    if (lExpr->type->asVec()) {
        const auto vecTy = lExpr->type->getIRType(cg);
        const auto vec = cg.builder.CreateLoad(vecTy, lExpr->IRValue);
        const auto c = lastExpr()->asVariable()->name;
        const auto i = cg.i32(LgsVec::getComponentIndex(c.front()));
        const auto insert = cg.builder.CreateInsertElement(vec, rIR, i);
        cg.builder.CreateStore(insert, lExpr->IRValue);
    } else {
        if (owner && type->isHeapAlloc) freeOwner(cg);
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
    if (toType->getName() == LgsAny::name) return this;
    if (type->getName() == toType->getName()) return this;
    assert(0);
}

Value* LgsSelection::hash(LgsLLVMGen& cg) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hash(cg);
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
