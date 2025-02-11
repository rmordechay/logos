#include "LogosBinaryExpr.h"

#include <llvm/IR/Module.h>

Value* LogosBinaryExpr::getLLVMValue(CodeGenMetadata* metadata) {
    const auto l = left->getLLVMValue(metadata);
    const auto r = right->getLLVMValue(metadata);
    if (op == PLUS) {
        return metadata->builder->CreateAdd(l, r);
    }
    if (op == RANGLE) {
        return metadata->builder->CreateICmpSGT(l, r);
    }
    return nullptr;
}

