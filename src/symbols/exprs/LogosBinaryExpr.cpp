#include "exprs/LogosBinaryExpr.h"

Value* LogosBinaryExpr::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto l = left->writeLLVMValue(metadata);
    const auto r = right->writeLLVMValue(metadata);
    if (op == PLUS) {
        llvmValue = metadata->builder->CreateAdd(l, r);
        return llvmValue;
    }
    if (op == RANGLE) {
        llvmValue = metadata->builder->CreateICmpSGT(l, r);
        return llvmValue;
    }
    return nullptr;
}

