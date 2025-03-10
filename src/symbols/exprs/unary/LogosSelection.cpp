#include "unary/LogosSelection.h"
#include "unary/LogosArrayIndex.h"
#include "unary/constants/LogosConstant.h"
#include "unary/LogosFuncCall.h"
#include "unary/LogosInstance.h"
#include "unary/LogosMethodCall.h"
#include "unary/LogosVariable.h"
#include "object/LogosField.h"
#include <LogosStack.h>

Value* LogosSelection::computeIRValue(CodeGenMetadata* metadata) {
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
    }
    break;
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

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, const int nextIndex, LogosInstance* instance) {
    const auto IRValue = instance->writeIRValue(metadata);
    if (innerExprs.size() == nextIndex) return IRValue;
    const auto nextExpr = innerExprs[nextIndex];
    if (dynamic_cast<LogosVariable*>(nextExpr)) {
        const auto fields = instance->obj->fields;
        const auto field = fields.find(nextExpr->getName());
        if (field != fields.end()) {
            return resolveInnerSelection(metadata, nextIndex + 1, field->second);
        }
    } else if (const auto methodCall = dynamic_cast<LogosMethodCall*>(nextExpr)) {
        auto methods = instance->obj->methods;
        const auto method = methods.find(nextExpr->getName());
        if (method != methods.end()) {
            const auto callIRValue = method->second->call(metadata, methodCall->args);
            methodCall->setIRValue(callIRValue);
            return resolveInnerSelection(metadata, nextIndex + 1, methodCall);
        }
    }
    return nullptr;
}

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, const int nextIndex, LogosMethodCall* methodCall) {
    const auto IRValue = methodCall->writeIRValue(metadata);
    if (innerExprs.size() == nextIndex) return IRValue;
    return nullptr;
}

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, const int nextIndex, LogosField* field) {
    const auto IRValue = field->writeIRValue(metadata);
    if (innerExprs.size() == nextIndex) return IRValue;
    return nullptr;
}

Value* LogosSelection::resolveInnerSelection(CodeGenMetadata* metadata, int nextIndex, LogosFuncImpl* funcImpl) {
    return nullptr;
}

string LogosSelection::getName() {
    return "";
}

LogosExpr* LogosSelection::lastExpr() const {
    return innerExprs[innerExprs.size() - 1];
}

LogosSelection::~LogosSelection() {
    delete firstExpr;
    for (const auto& expr : innerExprs) {
        delete expr;
    }
}
