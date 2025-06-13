#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

void LgsSelection::createIRStmt(LgsRuntime* runtime) {
    resolveSelection(runtime);
}

Value* LgsSelection::createIRValue(LgsRuntime* runtime) {
    resolveSelection(runtime);
    return lastExpr()->IRValue;
}

void LgsSelection::resolveSelection(LgsRuntime* runtime) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto methodCall = childExpr->asFuncCall()) {
            methodCall->IRValue = methodCall->createIRValue(runtime);
        } else if (const auto field = parentExpr->type->getField(childExpr->getName())) {
            const auto parentIRValue = parentExpr->getIRValue(runtime);
            const auto gep = field->getGEP(runtime, parentExpr->type->getIRType(), parentIRValue);
            childExpr->setIRValue(gep);
        }
    }
}

string LgsSelection::prettyName() {
    stringstream str;
    for (const auto expr : exprs) {
        str << '.' << expr->getName();
    }
    return str.str();
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
    resolveSelection(runtime);
    const auto selection = lastExpr();
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
