#include "stmts/LogosVarDec.h"

#include "LogosUtils.h"

#include <LogosStack.h>

Value* LogosVarDec::computeIRValue(CodeGenMetadata* metadata) {
    const auto value = expr->getIRValue(metadata);
    const auto valueType = value->getType();
    if (!valueType->isPointerTy()) {
        const auto builder = metadata->builder;
        const auto allocaInst = builder->CreateAlloca(valueType);
        builder->CreateStore(value, allocaInst);
    }
    const auto symbol = Utils::createSymbol(expr);
    metadata->theStack->addLocalSymbol(name, symbol);
    return value;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
