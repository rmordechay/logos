#include "exprs/LogosArrayIndex.h"

Value* LogosArrayIndex::computeIRValue(CodeGenMetadata* metadata) {
    const auto builder = metadata->builder;
    const auto irType = type->getIRType();
    const auto arr = metadata->module->getOrInsertGlobal("arr", irType);
    const ArrayRef<Value*> indices = {builder->getInt32(0), builder->getInt32(0)};
    const auto firstElement = builder->CreateGEP(irType, arr, indices);
    return builder->CreateLoad(builder->getInt32Ty(), firstElement);
}

LogosSymbolType LogosArrayIndex::getSymbolType() {
    return ARRAY_INDEX;
}

string LogosArrayIndex::getName() {
    return baseExpr->getName();
}
