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

void LgsSelection::createIRStmt(LgsRuntime* runtime) {
    resolveSelection(runtime);
}

Value* LgsSelection::createIRValue(LgsRuntime* runtime) {
    return resolveSelection(runtime)->IRValue;
}

LgsExpr* LgsSelection::resolveSelection(LgsRuntime* runtime) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        const auto field = parentExpr->type->getField(childExpr->getName());
        if (field) {
            const auto fieldIRType = field->type->getIRType(runtime);
            if (const auto iterIndex = parentExpr->asIterIndex()) {
                const auto gep = iterIndex->getGEP(runtime);
                auto valueLoad = runtime->builder.CreateLoad(runtime->builder.getPtrTy(), gep);
                const auto value = field->getGEP(runtime, valueLoad);
                valueLoad = runtime->builder.CreateLoad(fieldIRType, value);
                childExpr->setIRValue(valueLoad);
            } else {
                const auto parentIRValue = parentExpr->getIRValue(runtime);
                const auto value = field->getGEP(runtime, parentIRValue);
                const auto valueLoad = runtime->builder.CreateLoad(fieldIRType, value);
                childExpr->setIRValue(valueLoad);
            }
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            methodCall->IRValue = methodCall->createIRValue(runtime);
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

uint32_t LgsSelection::hashValue(LgsRuntime* runtime) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hashValue(runtime);
}

Value* LgsSelection::eqIR(LgsRuntime* runtime, LgsExpr* other) {
    const auto selection = resolveSelection(runtime);
    if (const auto var = selection->asVariable()) {
        return var->eqIR(runtime, other);
    }
    return nullptr;
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
