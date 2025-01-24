#include "LogosPrint.h"

Function* LogosPrint::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const auto printFuncType = FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(), false);
    return Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
}