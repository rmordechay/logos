#include "unary/LgsInstance.h"
#include "CodeGenerator.h"

Value* LgsInstance::createIRValue(CodeGenMetadata* metadata) {
    const auto value = getInstanceIRValue(metadata);
    if (!moduleExists(obj->name)) {
        CodeGenerator::generateModule(obj, metadata->logosStack.globalSymbols, metadata->buildDir);
    }
    return value;
}

string LgsInstance::getName() {
    return obj->name;
}

Value* LgsInstance::getInstanceIRValue(CodeGenMetadata* metadata) const {
    const auto currentFunc = metadata->logosStack.currentFunc;
    if (currentFunc->arg_size() > 0) {
        const auto firstArg = currentFunc->arg_begin();
        if (firstArg->getName() == LOGOS_SELF) return firstArg;
        return metadata->builder.CreateAlloca(obj->getIRType());
    }
    return metadata->builder.CreateAlloca(obj->getIRType());
}

LgsInstance::~LgsInstance() {
    if (obj) delete obj;
}

