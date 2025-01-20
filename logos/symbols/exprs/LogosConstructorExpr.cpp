#include "LogosConstructorExpr.h"

Value* LogosConstructorExpr::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    return builder->CreateAlloca(builder->getInt32Ty());
}
