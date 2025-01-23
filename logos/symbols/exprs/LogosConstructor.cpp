#include "LogosConstructor.h"

Value* LogosConstructor::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto logosSymbol = stackFrame->getSymbol(name);
    return builder->CreateAlloca(logosSymbol->llvmType);
}
