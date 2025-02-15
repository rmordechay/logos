#include "exprs/LogosSelection.h"

#include "LogosUtils.h"
#include "exprs/LogosFuncCall.h"

void resolveSelection(CodeGenMetadata* metadata, LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = metadata->theStack->getSymbol(previousExpr->getName());
    switch (symbol->type) {
    case FIELD:
        break;
    case CONSTRUCTOR: {
        const auto obj = symbol->constructor->obj;
        const auto func = obj->funcs[nextExpr->getName()];
        func->getLLVMValue(metadata);
        std::cout << "" << std::endl;
    }
    break;
    case FUNC_CALL:
        break;
    case VARIABLE:
        break;
    case CONSTANT:
        break;
    default:
        break;
    }
}

Value* LogosSelection::getLLVMValue(CodeGenMetadata* metadata) {
    auto previous = exprs[0];
    for (int i = 1; i < exprs.size(); ++i) {
        const auto next = exprs[i];
        resolveSelection(metadata, previous, next);
        previous = next;
    }
    return nullptr;
}

LogosSymbolType LogosSelection::getSymbolType() {
    return SELECTION;
}

LogosSelection::~LogosSelection() {
    for (const auto expr : exprs) {
        delete expr;
    }
}
