#include "LogosConstructor.h"

Value* LogosConstructor::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const auto logosSymbol = theStack->getSymbol(name)->object;
    const auto llvmType = logosSymbol->getLLVMType(builder, theStack);
    return builder->CreateAlloca(llvmType);
}
