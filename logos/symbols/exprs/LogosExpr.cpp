#include "LogosExpr.h"

#include "LogosBinaryExpr.h"
#include "LogosUnaryExpr.h"

Value* LogosExpr::getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) {
    if (const auto unary = dynamic_cast<LogosUnaryExpr*>(this)) {
        return unary->getLLVMValue(builder, stackFrame, module);
    }
    if (const auto binary = dynamic_cast<LogosBinaryExpr*>(this)) {
        return binary->getLLVMValue(builder, stackFrame, module);
    }
    return nullptr;
}