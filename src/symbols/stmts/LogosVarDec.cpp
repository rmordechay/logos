#include "stmts/LogosVarDec.h"

#include "LogosUtils.h"

#include <LogosStack.h>

Value* LogosVarDec::computeIRValue(CodeGenMetadata* metadata) {
    const auto value = expr->writeIRValue(metadata);
    const auto valueType = value->getType();
    if (!valueType->isPointerTy()) {
        auto& builder = metadata->builder;
        const auto allocaInst = builder.CreateAlloca(valueType);
        const auto instruction = "%1 = alloca i32, align 4";
        builder.CreateStore(value, allocaInst);
    }
    const auto symbol = LogosSymbol::createSymbol(expr);
    metadata->logosStack.addLocalSymbol(name, symbol);
    return value;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
