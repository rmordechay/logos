#include "LogosVariableExpr.h"

const LogosType& LogosVariableExpr::getType() const {
    return type;
}

Value* LogosVariableExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) {
    const auto symbol = stackFrame->symbolTable[name];
    return builder->CreateLoad(symbol->getAllocatedType(), symbol);
}
