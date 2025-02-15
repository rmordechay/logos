#include "exprs/LogosConstant.h"

Value* LogosConstant::getLLVMValue(CodeGenMetadata* metadata) {
    if (llvmValue) return llvmValue;
    if (const auto intValue = get_if<int>(&value)) {
        llvmValue = metadata->builder->getInt32(*intValue);
        return llvmValue;
    }
    return nullptr;
}

LogosConstant* LogosConstant::asConstant() {
    return this;
}
