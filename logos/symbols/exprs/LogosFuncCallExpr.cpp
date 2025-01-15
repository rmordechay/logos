#include "LogosFuncCallExpr.h"

const LogosType& LogosFuncCallExpr::getType() const {
    return type;
}

Value* LogosFuncCallExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) {
    return nullptr;
}
