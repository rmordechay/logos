#include "exprs/LogosInstance.h"

#include "CodeGenerator.h"

Value* LogosInstance::computeIRValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->logosStack.getSymbol(name)->object;
    if (modules.find(obj->name()) == modules.end()) {
        CodeGenerator::generateObjModule(obj, metadata->logosStack.globalSymbols);
    }
    const auto IRType = obj->getIRType();
    return metadata->builder.CreateAlloca(IRType);
}

LogosSymbolType LogosInstance::getSymbolType() {
    return INSTANCE;
}

void LogosInstance::setName(const string name) {
    this->name = name;
}

string LogosInstance::getName() {
    return name;
}
