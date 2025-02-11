#include "LogosConstructor.h"

Value* LogosConstructor::getLLVMValue(CodeGenMetadata* metadata) {
    const auto logosSymbol = metadata->theStack->getSymbol(name)->object;
    const auto llvmType = logosSymbol->getLLVMType(metadata->builder, metadata->theStack);
    return metadata->builder->CreateAlloca(llvmType);
}
