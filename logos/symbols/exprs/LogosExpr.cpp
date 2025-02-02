#include "LogosExpr.h"

#include "LogosBinaryExpr.h"
#include "LogosUnaryExpr.h"

Value* LogosExpr::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    if (const auto unary = dynamic_cast<LogosUnaryExpr*>(this)) {
        return unary->getLLVMValue(builder, theStack, module);
    }
    if (const auto binary = dynamic_cast<LogosBinaryExpr*>(this)) {
        return binary->getLLVMValue(builder, theStack, module);
    }
    return nullptr;
}