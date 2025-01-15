#include "LogosConstantExpr.h"

const LogosType& LogosConstantExpr::getType() const {
    return type;
}

Value* LogosConstantExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) {
    if (const auto intValue = get_if<int>(&value)) {
        return builder->getInt32(*intValue);
    }
    return nullptr;
}