#include "exprs/LogosArrayIndex.h"

#include <llvm/IR/Module.h>

Value* LogosArrayIndex::computeIRValue(CodeGenMetadata* metadata) {
    const auto builder = metadata->builder;
    const auto irType = type->getIRType();
    const auto arr = metadata->module->getOrInsertGlobal("arr", irType);
    const auto firstElement = builder->CreateGEP(irType, arr, builder->getInt32(1));
    return builder->CreateLoad(builder->getInt32Ty(), firstElement);
}

LogosSymbolType LogosArrayIndex::getSymbolType() {
    return ARRAY_INDEX;
}

string LogosArrayIndex::getName() {
    return baseExpr->getName();
}
