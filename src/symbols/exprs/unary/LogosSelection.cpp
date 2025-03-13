#include "unary/LogosSelection.h"
#include "unary/LogosArrayIndex.h"
#include "constants/LogosConstant.h"
#include "unary/LogosMethodCall.h"
#include "unary/LogosVariable.h"
#include "stmts/LogosField.h"
#include <LogosStack.h>

Value* LogosSelection::createIRValue(CodeGenMetadata* metadata) {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        if (const auto field = currentExpr->type->getField(nextExpr->getName())) {
            const auto value = field->getIRValue(metadata);
            nextExpr->setIRValue(value);
        } else if (const auto method = currentExpr->type->getMethod(nextExpr->getName())) {
            const auto methodCall = dynamic_cast<LogosMethodCall*>(nextExpr);
            const auto value = method->call(metadata, methodCall->args);
            nextExpr->setIRValue(value);
        }
    }
    return lastExpr()->getIRValue(metadata);
}

Value* LogosSelection::resolveSelectionVariable(CodeGenMetadata* metadata, const LogosVariable* variable, LogosUnaryExpr* nextExpr) const {
    const auto nextExprName = nextExpr->getName();
    const auto currentSymbol = metadata->logosStack.getSymbol(variable->name);
    LogosField* field = nullptr;
    if (currentSymbol->type == VAR_DEC) {
        const auto varDec = currentSymbol->varDec;
        field = varDec->type->getField(nextExprName);
    } else if (currentSymbol->type == PARAM) {
        const auto param = currentSymbol->param;
        field = param->type->getField(nextExprName);
    }
    if (field) {
        return field->getIRValue(metadata);
    }
    if (const auto methodCall = dynamic_cast<LogosMethodCall*>(nextExpr)) {
        return methodCall->createIRValue(metadata);
    }
    return nullptr;
}

Value* LogosSelection::resolveType(CodeGenMetadata* metadata, LogosUnaryExpr* nextExpr, LogosType* logosType) const {
    const auto nextExprName = nextExpr->getName();
    if (const auto field = logosType->getField(nextExprName)) {
        return field->getIRValue(metadata);
    }
    if (const auto method = logosType->getMethod(nextExprName)) {
        return method->getIRValue(metadata);
    }
    return nullptr;
}

string LogosSelection::getName() {
    return "";
}

LogosExpr* LogosSelection::lastExpr() const {
    if (exprs.empty()) return nullptr;
    return exprs[exprs.size() - 1];
}

LogosSelection::~LogosSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
