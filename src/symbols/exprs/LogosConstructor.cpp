#include "exprs/LogosConstructor.h"

#include "CodeGenerator.h"

string LogosConstructor::getName() {
    return name;
}

LogosSymbolType LogosConstructor::getSymbolType() {
    return CONSTRUCTOR;
}

Value* LogosConstructor::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->theStack->getSymbol(name)->object;
    // TODO make modules a map to check if they were already generated
    CodeGenerator::generateObjModule(obj, metadata->theStack);
    const auto llvmType = obj->getLLVMType();
    return metadata->builder->CreateAlloca(llvmType);
}