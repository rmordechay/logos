#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

void LgsSelection::createIRStmt(LgsModule* module) {
    resolveSelection(module);
}

Value* LgsSelection::createIRValue(LgsModule* module) {
    resolveSelection(module);
    return lastExpr()->IRValue;
}

void LgsSelection::resolveSelection(LgsModule* module) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto methodCall = childExpr->asFuncCall()) {
            methodCall->IRValue = methodCall->getIRValue(module);
        } else {
            const auto field = parentExpr->type->getField(childExpr->getExprName());
            Value* v = nullptr;
            if (field->type->asEnum()) {
                if (field->expr) {
                    v = field->expr->getIRValue(module);
                } else {
                    v = getIRStr(module, field->name);
                }
            } else {
                const auto parentIRValue = parentExpr->getIRValue(module);
                const auto parentIRType = parentExpr->type->getIRType(module);
                v = field->getGEP(module, parentIRType, parentIRValue);
            }
            childExpr->setIRValue(v);
        }
    }
}

string LgsSelection::prettyName() {
    stringstream str;
    str << exprs[0]->prettyName();
    for (int i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->prettyName();
    }
    return str.str();
}

LgsExpr* LgsSelection::lastExpr() const {
    if (exprs.empty()) return nullptr;
    return exprs[exprs.size() - 1];
}

Value* LgsSelection::hashValue(LgsModule* module) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hashValue(module);
}

Value* LgsSelection::eqIR(LgsModule* module, LgsExpr* other) {
    resolveSelection(module);
    const auto selection = lastExpr();
    if (const auto var = selection->asVariable()) {
        return var->eqIR(module, other);
    }
    return nullptr;
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
