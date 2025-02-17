#include "exprs/LogosInstance.h"

#include "CodeGenerator.h"

string LogosInstance::getName() {
    return name;
}

LogosSymbolType LogosInstance::getSymbolType() {
    return INSTANCE;
}

Value* LogosInstance::computeIRValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->theStack->getSymbol(name)->object;
    // TODO make modules a map to check if they were already generated
    CodeGenerator::generateObjModule(obj, metadata->theStack);
    const auto IRType = obj->getIRType();
    return metadata->builder->CreateAlloca(IRType);
}