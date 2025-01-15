#include "LogosBinaryExpr.h"

const LogosType& LogosBinaryExpr::getType() const {
    return type;
}

Value* LogosBinaryExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) {
    const auto l = left->getLLVMValue(builder, stackFrame);
    const auto r = right->getLLVMValue(builder, stackFrame);
    if (op == PLUS) {
        return builder->CreateAdd(l, r);
    }
    if (op == RANGLE) {
        return builder->CreateICmpSGT(l, r);
    }
    return nullptr;
}

