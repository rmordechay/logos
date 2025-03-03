#include "exprs/LogosSelection.h"

#include "LogosUtils.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosFuncCall.h"
#include <LogosStack.h>
#include <object/LogosField.h>

Value* LogosSelection::computeIRValue(CodeGenMetadata* metadata) {
    Value* value = nullptr;
    for (size_t i = 0; i < exprs.size() - 1; ++i) {
        const auto previousExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        value = resolveSelection(metadata, previousExpr, nextExpr);
    }
    return value;
}

Value* LogosSelection::resolveSelection(CodeGenMetadata* metadata, LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = metadata->logosStack.getSymbol(previousExpr->getName());
    switch (symbol->type) {
    case INSTANCE: {
        const auto& funcName = nextExpr->getName();
        const auto obj = symbol->instance->obj;
        if (obj->funcs.contains(funcName)) {
            const auto func = obj->funcs[funcName];
            return func->callFunc(metadata, {previousExpr});
        }
        if (obj->fields.contains(funcName)) {
            const auto field = obj->fields[funcName];
            return nullptr;
        }
        break;
    }
    case FUNC_CALL: {
        return symbol->funcCall->writeIRValue(metadata);
    }
    default:
        break;
    }
    return nullptr;
}

LogosSymbolType LogosSelection::getSymbolType() {
    return SELECTION;
}

void LogosSelection::setName(string name) {}

string LogosSelection::getName() {
    return "";
}

LogosSelection::~LogosSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
