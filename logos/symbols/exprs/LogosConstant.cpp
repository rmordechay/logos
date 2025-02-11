#include "LogosConstant.h"

Value* LogosConstant::getLLVMValue(CodeGenMetadata* metadata) {
    if (const auto intValue = get_if<int>(&value)) {
        return metadata->builder->getInt32(*intValue);
    }
    return nullptr;
}