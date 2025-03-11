#include "unary/LogosInstance.h"

#include "CodeGenerator.h"

Value* LogosInstance::createIRValue(CodeGenMetadata* metadata) {
    const auto selfSymbol = metadata->logosStack.getSymbol(LOGOS_SELF);
    if (selfSymbol) {
        return selfSymbol->param->getIRValue(metadata);
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

LogosInstance::~LogosInstance() {
    if (obj) delete obj;
}

