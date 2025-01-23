#include "LogosConstant.h"

Value* LogosConstant::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    if (const auto intValue = get_if<int>(&value)) {
        return builder->getInt32(*intValue);
    }
    return nullptr;
}