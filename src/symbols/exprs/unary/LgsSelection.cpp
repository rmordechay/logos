#include "unary/LgsSelection.h"

#include "LgsFuncCall.h"
#include "unary/LgsArrayIndex.h"
#include "unary/LgsVariable.h"
#include "stmts/LgsField.h"

string LgsSelection::getName() {
    return "";
}

LgsExpr* LgsSelection::lastExpr() const {
    if (exprs.empty()) return nullptr;
    return exprs[exprs.size() - 1];
}

LgsExpr* LgsSelection::resolveSelection(CodeGenMetadata* metadata) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        if (const auto field = currentExpr->type->getField(nextExpr->getName())) {
            const auto value = field->getIRValue(metadata);
            nextExpr->setIRValue(value);
        } else if (const auto method = currentExpr->type->getMethod(nextExpr->getName())) {
            const auto methodCall = dynamic_cast<LgsFuncCall*>(nextExpr);
            const auto value = method->call(metadata, methodCall->args);
            nextExpr->setIRValue(value);
        }
    }
    return lastExpr();
}

Value* LgsSelection::createIRValue(CodeGenMetadata* metadata) {
    return resolveSelection(metadata)->getIRValue(metadata);
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
