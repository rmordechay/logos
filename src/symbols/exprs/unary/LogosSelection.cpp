#include "unary/LogosSelection.h"
#include "unary/LogosArrayIndex.h"
#include "constants/LogosConstant.h"
#include "unary/LogosFuncCall.h"
#include "unary/LogosInstance.h"
#include "unary/LogosMethodCall.h"
#include "unary/LogosVariable.h"
#include "stmts/LogosField.h"
#include <LogosStack.h>

Value* LogosSelection::createIRValue(CodeGenMetadata* metadata) {
    if (const auto variable = dynamic_cast<LogosVariable*>(firstExpr)) {
        return resolveFirstSelection(metadata, variable);
    }
    if (const auto funcCall = dynamic_cast<LogosFuncCall*>(firstExpr)) {
        return resolveFirstSelection(metadata, funcCall);
    }
    return nullptr;
}

Value* LogosSelection::resolveFirstSelection(CodeGenMetadata* metadata, const LogosVariable* variable) {
    const auto symbol = metadata->logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case VAR_DEC: {
        const auto varDecExpr = symbol->varDec->expr;
        if (const auto instance = dynamic_cast<LogosInstance*>(varDecExpr)) {
            return resolveInnerSelection(metadata, 0, instance);
        }
        return nullptr;
    }
    case PARAM: {
        const auto paramExpr = symbol->param->expr;
        if (const auto instance = dynamic_cast<LogosInstance*>(paramExpr)) {
            return resolveInnerSelection(metadata, 0, instance);
        }
    }
    default:
        break;
    }
    return nullptr;
}

Value* LogosSelection::resolveFirstSelection(CodeGenMetadata* metadata, const LogosFuncCall* funcCall) {
    const auto symbol = metadata->logosStack.getSymbol(funcCall->name);
    switch (symbol->type) {
    case FUNC_IMPL: {
        return resolveInnerSelection(metadata, 0, symbol->funcImpl);
    }
    default:
        break;
    }
    return nullptr;
}

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, const int i, LogosInstance* instance) {
    const auto IRValue = instance->getIRValue(metadata);
    if (innerExprs.size() == i) return IRValue;

    const auto nextExpr = innerExprs[i];
    if (const auto variable = dynamic_cast<LogosVariable*>(nextExpr)) {
        const auto field = instance->obj->getField(variable->name);
        field->instance = instance;
        return resolveInnerSelection(metadata, i + 1, field);
    }
    if (const auto methodCall = dynamic_cast<LogosMethodCall*>(nextExpr)) {
        methodCall->getIRValue(metadata);
        return resolveInnerSelection(metadata, i + 1, methodCall);
    }
    return nullptr;
}

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, const int i, LogosField* field) const {
    const auto IRValue = field->createIRValue(metadata);
    if (innerExprs.size() == i) return IRValue;
    return nullptr;
}

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, const int i, LogosMethodCall* methodCall) {
    const auto IRValue = methodCall->getIRValue(metadata);
    if (innerExprs.size() == i) return IRValue;
    return nullptr;
}

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosFuncImpl* funcImpl) {
    return nullptr;
}

string LogosSelection::getName() {
    return "";
}

LogosExpr* LogosSelection::lastExpr() const {
    if (innerExprs.empty()) return nullptr;
    return innerExprs[innerExprs.size() - 1];
}

LogosSelection::~LogosSelection() {
    delete firstExpr;
    for (const auto& expr : innerExprs) {
        delete expr;
    }
}
