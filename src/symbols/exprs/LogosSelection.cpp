#include "exprs/LogosSelection.h"

#include "LogosUtils.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosFuncCall.h"
#include "funcs/LogosUserFunc.h"

Value* LogosSelection::computeLLVMValue(CodeGenMetadata* metadata) {
    Value* value = nullptr;
    for (size_t i = 0; i < exprs.size() - 1; ++i) {
        const auto previousExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        value = resolveSelection(metadata, previousExpr, nextExpr);
    }
    return value;
}

Value* LogosSelection::resolveSelection(CodeGenMetadata* metadata, LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = metadata->theStack->getSymbol(previousExpr->getName());
    switch (symbol->type) {
    case CONSTRUCTOR: {
        const auto obj = symbol->constructor->obj;
        const auto func = obj->funcs[nextExpr->getName()];
        return func->callFunc(metadata);
    }
    case FUNC_CALL: {
        return symbol->funcCall->getLLVMValue(metadata);
    }
    default:
        break;
    }
    return nullptr;
}

LogosSymbolType LogosSelection::getSymbolType() {
    return SELECTION;
}

LogosSelection::~LogosSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
