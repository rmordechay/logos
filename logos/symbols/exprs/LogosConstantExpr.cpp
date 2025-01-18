#include "LogosConstantExpr.h"

Value* LogosConstantExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    if (const auto intValue = get_if<int>(&value)) {
        return builder->getInt32(*intValue);
    }
    return nullptr;
}