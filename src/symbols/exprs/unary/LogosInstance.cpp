#include "unary/LogosInstance.h"
#include "CodeGenerator.h"

Value* LogosInstance::createIRValue(CodeGenMetadata* metadata) {
    const auto value = getInstanceIRValue(metadata);
    if (!moduleExists(obj->name)) {
        CodeGenerator::generateModule(obj, metadata->logosStack.globalSymbols, metadata->buildDir);
    }
    return value;
}

string LogosInstance::getName() {
    return obj->name;
}

Value* LogosInstance::getInstanceIRValue(CodeGenMetadata* metadata) const {
    const auto currentFunc = metadata->logosStack.currentFunc;
    if (currentFunc->arg_size() > 0) {
        const auto firstArg = currentFunc->arg_begin();
        if (firstArg->getName() == LOGOS_SELF) return firstArg;
        return metadata->builder.CreateAlloca(obj->getIRType());
    }
    return metadata->builder.CreateAlloca(obj->getIRType());
}

LogosInstance::~LogosInstance() {
    if (obj) delete obj;
}

