#include "LogosPrint.h"

const LogosType& LogosPrint::getType() const {
    return type;
}

Value* LogosPrint::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    return nullptr;
}
