#include "exprs/LogosArrayIndex.h"

#include <exprs/LogosArray.h>
#include <exprs/LogosConstant.h>
#include <llvm/IR/Module.h>

Value* LogosArrayIndex::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto irType = type->getIRType();
    const auto arr = metadata->logosStack.getSymbol(baseExpr->getName());
    const auto lastExprIRValue = exprs[exprs.size() - 1]->writeIRValue(metadata);
    const auto arrPtr = arr->array->writeIRValue(metadata);
    const auto lastElement = builder.CreateGEP(irType, arrPtr, lastExprIRValue);
    return builder.CreateLoad(irType, lastElement);;
}

LogosSymbolType LogosArrayIndex::getSymbolType() {
    return ARRAY_INDEX;
}

void LogosArrayIndex::setName(const string name) {
    baseExpr->setName(name);
}

string LogosArrayIndex::getName() {
    return baseExpr->getName();
}
