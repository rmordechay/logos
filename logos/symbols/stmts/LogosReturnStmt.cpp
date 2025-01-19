#include "LogosReturnStmt.h"

Value* LogosReturnStmt::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto exprLLVM = expr->getLLVMValue(builder, stackFrame, module);
    return builder->CreateRet(exprLLVM);
}
