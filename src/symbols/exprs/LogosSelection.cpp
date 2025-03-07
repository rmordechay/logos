#include "exprs/LogosSelection.h"
#include "LogosUtils.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosFuncCall.h"
#include <LogosStack.h>

Value* LogosSelection::computeIRValue(CodeGenMetadata* metadata) {
    Value* value = nullptr;
    const auto firstExpr = exprs[0];
    const auto secondExpr = exprs[1];
    value = resolveSelection(metadata, firstExpr, secondExpr);
    return value;
}

LogosExpr* LogosSelection::getLastExpr() const {
    return exprs[exprs.size() - 1];
}

Value* LogosSelection::resolveSelection(CodeGenMetadata* metadata, LogosUnaryExpr* firstExpr, LogosUnaryExpr* secondExpr) {
    const auto symbol = metadata->logosStack.getSymbol(firstExpr->getName());
    switch (symbol->type) {
    case VAR_DEC: {
        if (const auto instance = dynamic_cast<LogosInstance*>(symbol->varDec->expr)) {
            resolveInstance(metadata, instance, secondExpr);
        }
        break;
    }
    default:
        break;
    }
    return nullptr;
}

void LogosSelection::resolveInstance(CodeGenMetadata* metadata, const LogosInstance* instance, LogosExpr* expr) {
    auto methods = instance->obj->methods;
    if (const auto funcCall = dynamic_cast<LogosFuncCall*>(expr)) {
        const auto funcCallName = funcCall->name;
        const auto method = methods[funcCallName];
        method->call(metadata, funcCall->args);
    }
}

string LogosSelection::getName() {
    return "";
}

LogosSelection::~LogosSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
