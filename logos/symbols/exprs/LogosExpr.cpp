#include "LogosExpr.h"

#include "LogosBinaryExpr.h"
#include "LogosUnaryExpr.h"

const LogosType& LogosExpr::getType() const {
    return type;
}

Value* LogosExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    if (const auto unary = dynamic_cast<LogosUnaryExpr*>(this)) {
        return unary->getLLVMValue(builder, stackFrame, module);
    }
    if (const auto binary = dynamic_cast<LogosBinaryExpr*>(this)) {
        return binary->getLLVMValue(builder, stackFrame, module);
    }
    return nullptr;
}