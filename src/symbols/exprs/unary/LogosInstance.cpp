#include "unary/LogosInstance.h"

#include "CodeGenerator.h"

Value* LogosInstance::computeIRValue(CodeGenMetadata* metadata) {
    const auto selfSymbol = metadata->logosStack.getSymbol(LOGOS_SELF);
    if (selfSymbol) {
        return selfSymbol->param->writeIRValue(metadata);
    }

    const auto objSymbol = metadata->logosStack.getSymbol(obj->name)->object;
    if (modules.find(objSymbol->getName()) == modules.end()) {
        CodeGenerator::generateObjectModule(objSymbol, metadata->logosStack.globalSymbols);
    }
    const auto IRType = objSymbol->getIRType();
    return metadata->builder.CreateAlloca(IRType);
}

string LogosInstance::getName() {
    return obj->name;
}

