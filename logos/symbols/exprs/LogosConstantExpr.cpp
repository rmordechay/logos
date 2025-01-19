#include "LogosConstantExpr.h"

Value* LogosConstantExpr::getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) {
    if (const auto intValue = get_if<int>(&value)) {
        return builder->getInt32(*intValue);
    }
    return nullptr;
}