#include "LogosConstructor.h"

Value* LogosConstructor::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const auto logosSymbol = theStack->globalSymbols[name];
    return builder->CreateAlloca(logosSymbol->llvmType);
}
