#include "exprs/LogosInstance.h"

#include "CodeGenerator.h"

Value* LogosInstance::computeIRValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->theStack->getSymbol(name)->object;
    // TODO make modules a map to check if they were already generated
    CodeGenerator::generateObjModule(obj, TODO);
    const auto IRType = obj->getIRType();
    return metadata->builder->CreateAlloca(IRType);
}

LogosSymbolType LogosInstance::getSymbolType() {
    return INSTANCE;
}

string LogosInstance::getName() {
    return name;
}
