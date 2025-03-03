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
        const auto& exprName = nextExpr->getName();
        const auto instance = symbol->instance;
        const auto obj = instance->obj;
        const auto objType = instance->obj->getIRType();
        if (obj->funcs.contains(exprName)) {
            const auto func = obj->funcs[exprName];
            return func->callFunc(metadata, {previousExpr});
        }
        if (obj->fields.contains(exprName)) {
            const auto field = obj->fields[exprName];
            const auto instancePtr = instance->writeIRValue(metadata);
            const auto gep = metadata->builder.CreateStructGEP(objType, instancePtr, field->fieldPosition);
            return metadata->builder.CreateLoad(field->inferredType->getIRType(), gep);
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
