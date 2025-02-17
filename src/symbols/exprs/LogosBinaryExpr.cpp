#include "exprs/LogosBinaryExpr.h"

Value* LogosBinaryExpr::computeIRValue(CodeGenMetadata* metadata) {
    const auto l = left->getIRValue(metadata);
    const auto r = right->getIRValue(metadata);
    if (op == PLUS) {
        return metadata->builder->CreateAdd(l, r);
    }
    if (op == RANGLE) {
        return metadata->builder->CreateICmpSGT(l, r);
    }
    return nullptr;
}

