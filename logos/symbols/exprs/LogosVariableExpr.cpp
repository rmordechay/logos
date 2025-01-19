#include "LogosVariableExpr.h"

Value* LogosVariableExpr::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto symbol = stackFrame->getSymbol(name);
    if (auto const allocaInst = dyn_cast<AllocaInst>(symbol)) {
        return builder->CreateLoad(allocaInst->getAllocatedType(), allocaInst);
    }
    return nullptr;
}
