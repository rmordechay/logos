#include "exprs/LogosInstance.h"

#include "CodeGenerator.h"

Value* LogosInstance::computeIRValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->logosStack.getSymbol(name)->object;
    if (modules.find(obj->getName()) == modules.end()) {
        CodeGenerator::generateObjectModule(obj, metadata->logosStack.globalSymbols);
    }
    const auto IRType = obj->getIRType();
    return metadata->builder.CreateAlloca(IRType);
}


string LogosInstance::getName() {
    return name;
}
