#include "exprs/LogosConstant.h"

Value* LogosConstant::writeLLVMValue(CodeGenMetadata* metadata) {
    if (const auto intValue = get_if<int>(&value)) {
        llvmValue = metadata->builder->getInt32(*intValue);
        return llvmValue;
    }
    return nullptr;
}