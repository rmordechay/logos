#include "LogosVariableExpr.h"

#include "LogosDefinitions.h"

#include <llvm/IR/Module.h>

Value* LogosVariable::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto symbol = stackFrame->getSymbol(name);
    if (const auto val = symbol->llvmValue) {
        if (auto const allocaInst = dyn_cast<AllocaInst>(val)) {
            return builder->CreateLoad(allocaInst->getAllocatedType(), allocaInst);
        }
    } else if (const auto type = symbol->llvmType) {
        const auto allocaInst = builder->CreateAlloca(type);
        const auto logosSymbol = stackFrame->getSymbol(name)->llvmType;
        const auto structGep = builder->CreateStructGEP(logosSymbol, allocaInst, symbol->pos);
        return builder->CreateLoad(allocaInst->getAllocatedType(), structGep);
    }
    return nullptr;
}
