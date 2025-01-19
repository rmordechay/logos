#include "LogosVariableExpr.h"

#include "LogosDefinitions.h"

Value* LogosVariableExpr::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto symbol = stackFrame->getSymbol(name);
    if (const auto val = symbol->symbolValue) {
        if (auto const allocaInst = dyn_cast<AllocaInst>(val)) {
            return builder->CreateLoad(allocaInst->getAllocatedType(), allocaInst);
        }
    } else if (const auto type = symbol->symbolType) {
        const auto allocaInst = builder->CreateAlloca(type);
        const auto logosSymbol = stackFrame->getSymbol(LOGOS_THIS)->symbolType;
        return builder->CreateStructGEP(logosSymbol, allocaInst, symbol->pos);
    }
    return nullptr;
}
