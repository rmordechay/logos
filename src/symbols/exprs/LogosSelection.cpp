#include "exprs/LogosSelection.h"
#include "LogosUtils.h"
#include "exprs/LogosArrayIndex.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosVariable.h"
#include "object/LogosField.h"

#include <LogosStack.h>

Value* LogosSelection::computeIRValue(CodeGenMetadata* metadata) {
    Value* value = nullptr;
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto prevExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        if (const auto variable = dynamic_cast<LogosVariable*>(prevExpr)) {
            value = resolveSelection(metadata, variable, nextExpr);
        }
    }
    return value;
}

Value* LogosSelection::resolveSelection(CodeGenMetadata* metadata, const LogosVariable* variable, LogosUnaryExpr* nextExpr) const {
    const auto symbol = metadata->logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case VAR_DEC:
        if (const auto instance = dynamic_cast<LogosInstance*>(symbol->varDec->expr)) {
            if (const auto funcCall = dynamic_cast<LogosFuncCall*>(nextExpr)) {
                const auto method = instance->obj->methods[funcCall->name];
                return method->call(metadata, funcCall->args);
            }
            if (const auto field = dynamic_cast<LogosField*>(nextExpr)) {
                const auto v = instance->obj->fields[field->name];
                return v->writeIRValue(metadata);
            }
        }
        break;
    default:
        break;;
    }
    return nullptr;
}

string LogosSelection::getName() {
    return "";
}

LogosExpr* LogosSelection::getLastExpr() const {
    return exprs[exprs.size() - 1];
}

LogosSelection::~LogosSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
