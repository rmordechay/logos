#include "LogosBinaryExpr.h"

Value* LogosBinaryExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    const auto l = left->getLLVMValue(builder, stackFrame, module);
    const auto r = right->getLLVMValue(builder, stackFrame, module);
    if (op == PLUS) {
        return builder->CreateAdd(l, r);
    }
    if (op == RANGLE) {
        return builder->CreateICmpSGT(l, r);
    }
    return nullptr;
}

