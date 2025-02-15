#include "exprs/LogosBinaryExpr.h"

Value* LogosBinaryExpr::getLLVMValue(CodeGenMetadata* metadata) {
    if (llvmValue) return llvmValue;
    const auto l = left->getLLVMValue(metadata);
    const auto r = right->getLLVMValue(metadata);
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

