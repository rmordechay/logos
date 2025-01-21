#include "LogosConstructorExpr.h"

Value* LogosConstructorExpr::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto logosSymbol = stackFrame->getSymbol(name);
    return builder->CreateAlloca(logosSymbol->llvmType);
}
