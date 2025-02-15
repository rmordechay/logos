#include "exprs/LogosConstructor.h"

#include "CodeGenerator.h"

Value* LogosConstructor::getLLVMValue(CodeGenMetadata* metadata) {
    if (llvmValue) return llvmValue;
    const auto obj = metadata->theStack->getSymbol(name)->object;
    CodeGenerator::generateObjModule(obj, metadata->theStack);
    const auto llvmType = obj->getLLVMType();
    llvmValue = metadata->builder->CreateAlloca(llvmType);
    return llvmValue;
}

LogosConstructor* LogosConstructor::asConstructor() {
    return this;
}
