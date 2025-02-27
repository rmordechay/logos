#include "exprs/LogosArrayIndex.h"

#include <exprs/LogosConstant.h>
#include <llvm/IR/Module.h>

Value* LogosArrayIndex::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto irType = type->getIRType();
    const auto arr = metadata->currentModule->getOrInsertGlobal("arr", irType);
    const auto lastExprIRValue = exprs[exprs.size() - 1]->writeIRValue(metadata);
    const auto lastElement = builder.CreateGEP(irType, arr, lastExprIRValue);
    return builder.CreateLoad(builder.getInt32Ty(), lastElement);
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
