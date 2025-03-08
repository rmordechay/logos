#include "stmts/LogosVarDec.h"
#include "exprs/LogosConstant.h"
#include <LogosStack.h>

Value* LogosVarDec::computeIRValue(CodeGenMetadata* metadata) {
    Value* value;
    if (expr) {
        value = expr->writeIRValue(metadata);
    } else {
        value = type->getZeroValue()->writeIRValue(metadata);
    }
    const auto valueType = value->getType();
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
