#include "exprs/LogosInstance.h"

#include "CodeGenerator.h"

string LogosInstance::getName() {
    return name;
}

LogosSymbolType LogosInstance::getSymbolType() {
    return INSTANCE;
}

Value* LogosInstance::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->theStack->getSymbol(name)->object;
    // TODO make modules a map to check if they were already generated
    CodeGenerator::generateObjModule(obj, metadata->theStack);
    const auto llvmType = obj->getLLVMType();
    return metadata->builder->CreateAlloca(llvmType);
}