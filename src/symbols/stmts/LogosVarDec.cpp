#include "stmts/LogosVarDec.h"

#include "LogosUtils.h"
#include "exprs/LogosConstant.h"

#include <LogosStack.h>

Value* LogosVarDec::computeIRValue(CodeGenMetadata* metadata) {
    if (expr) {
        const auto value = expr->writeIRValue(metadata);
        const auto valueType = value->getType();
        if (!valueType->isPointerTy()) {
            auto& builder = metadata->builder;
            const auto allocaInst = builder.CreateAlloca(valueType);
            builder.CreateStore(value, allocaInst);
        }
        const auto symbol = LogosSymbol::createSymbol(expr);
        metadata->logosStack.addLocalSymbol(name, symbol);
        return value;
    }
    return inferredType->getZeroValue()->writeIRValue(metadata);
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
