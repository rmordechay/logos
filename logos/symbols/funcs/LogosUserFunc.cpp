#include "LogosUserFunc.h"

const LogosType& LogosUserFunc::getType() const {
    return type;
}

Value* LogosUserFunc::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) {
    return nullptr;
}
