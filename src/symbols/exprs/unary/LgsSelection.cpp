#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"

string LgsSelection::getName() {
    return "";
}

Value* LgsSelection::createIRValue(CodeGenMetadata* metadata) {
    return resolveSelection(metadata)->getIRValue(metadata);
}

LgsExpr* LgsSelection::resolveSelection(CodeGenMetadata* metadata) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        if (const auto field = currentExpr->type->getField(nextExpr->getName())) {
            const auto value = field->getIRValue(metadata);
            field->parentExpr = currentExpr;
            nextExpr->setIRValue(value);
            continue;
        }
        if (const auto methodCall = nextExpr->asFuncCall()) {
            nextExpr->setIRValue(methodCall->getIRValue(metadata));
        }
    }
    return lastExpr();
}

LgsExpr* LgsSelection::lastExpr() const {
    if (exprs.empty()) return nullptr;
    return exprs[exprs.size() - 1];
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
