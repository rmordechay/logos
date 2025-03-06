#include "stmts/LogosVarDec.h"

#include "LogosUtils.h"
#include "exprs/LogosConstant.h"

#include <LogosStack.h>

Value* LogosVarDec::computeIRValue(CodeGenMetadata* metadata) {
    Value* value;
    Type* valueType;
    if (expr) {
        value = expr->writeIRValue(metadata);
        valueType = value->getType();
    } else {
        value = type->getZeroValue()->writeIRValue(metadata);
        valueType = value->getType();
    }
    if (!valueType->isPointerTy()) {
        auto& builder = metadata->builder;
        const auto allocaInst = builder.CreateAlloca(valueType);
        builder.CreateStore(value, allocaInst);
    }
    metadata->logosStack.addLocalSymbol(name, LogosSymbol(VAR_DEC, this));
    return value;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
