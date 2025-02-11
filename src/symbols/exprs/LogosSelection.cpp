#include "exprs/LogosSelection.h"

#include "LogosUtils.h"

#include <exprs/LogosVariableExpr.h>

Value* LogosSelection::getLLVMValue(CodeGenMetadata* metadata) {
    for (int i = 0; i < exprs.size(); ++i) {
        const auto currentExpr = exprs[i];
        const bool isLastIteration = i == exprs.size() - 1;
        if (isLastIteration) {
            return currentExpr->getLLVMValue(metadata);
        }

        const auto nextExpr = exprs[i + 1];
        const auto n = Utils::getUnaryExprName(nextExpr);
        if (const auto var = dynamic_cast<LogosVariable*>(currentExpr)) {
            const auto objSymbol = metadata->theStack->getSymbol(var->name);
            const auto typeName = objSymbol->varDec->inferredType->name();
            const auto obj = metadata->theStack->getSymbol(typeName)->object;

        }
    }
    return nullptr;
}

LogosSelection::~LogosSelection() {
    for (const auto expr : exprs) {
        delete expr;
    }
}

