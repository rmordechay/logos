#include "LogosConstructor.h"

#include "CodeGenerator.h"

Value* LogosConstructor::getLLVMValue(CodeGenMetadata* metadata) {
    const auto obj = metadata->theStack->getSymbol(name)->object;
    CodeGenerator::generateObjModule(obj, metadata->builder, metadata->theStack);
    const auto llvmType = obj->getLLVMType(metadata->builder, metadata->theStack);
    return metadata->builder->CreateAlloca(llvmType);
}
