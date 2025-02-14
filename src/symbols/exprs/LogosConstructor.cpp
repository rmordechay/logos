#include "exprs/LogosConstructor.h"

#include "CodeGenerator.h"

Value* LogosConstructor::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->theStack->getSymbol(name)->object;
    CodeGenerator::generateObjModule(obj, metadata->theStack);
    const auto llvmType = obj->writeLLVMType(metadata);
    llvmValue = metadata->builder->CreateAlloca(llvmType);
    return llvmValue;
}
