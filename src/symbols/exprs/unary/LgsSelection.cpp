#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"

string LgsSelection::getName() {
    return "";
}

void LgsSelection::createIRStmt(Module* module) {
    resolveSelection(module);
}

Value* LgsSelection::createIRValue(Module* module) {
    return resolveSelection(module)->IRValue;
}

LgsExpr* LgsSelection::resolveSelection(Module* module) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        const auto field = parentExpr->type->getField(childExpr->getName());
        if (field) {
            if (const auto iterIndex = parentExpr->asIterIndex()) {
                const auto gep = iterIndex->getGEP(module);
                auto valueLoad = builder.CreateLoad(ptrTy, gep);
                const auto value = field->getGEP(module, valueLoad);
                valueLoad = builder.CreateLoad(field->type->getIRType(), value);
                childExpr->setIRValue(valueLoad);
            } else {
                const auto parentIRValue = parentExpr->getIRValue(module);
                const auto value = field->getGEP(module, parentIRValue);
                const auto valueLoad = builder.CreateLoad(field->type->getIRType(), value);
                childExpr->setIRValue(valueLoad);
            }
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            methodCall->IRValue = methodCall->createIRValue(module);
        }
    }
    return lastExpr();
}

json LgsSelection::asJSON() {
    json tree;
    tree["exprs"] = {};
    tree["exprType"] = "SELECTION";
    for (const auto& expr : exprs) {
        tree["exprs"].emplace_back(expr->asJSON());
    }
    return tree;
}

LgsExpr* LgsSelection::lastExpr() const {
    if (exprs.empty()) return nullptr;
    return exprs[exprs.size() - 1];
}

uint32_t LgsSelection::hashValue(Module* module) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hashValue(module);
}

Value* LgsSelection::eqIR(Module* module, LgsExpr* other) {
    const auto selection = resolveSelection(module);
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
