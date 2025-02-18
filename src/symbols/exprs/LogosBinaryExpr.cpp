#include "exprs/LogosBinaryExpr.h"

Value* LogosBinaryExpr::computeIRValue(CodeGenMetadata* metadata) {
    const auto l = left->getIRValue(metadata);
    const auto r = right->getIRValue(metadata);
    const auto builder = metadata->builder;
    if (op == PLUS) {
        return builder->CreateAdd(l, r);
    }
    if (op == RANGLE) {
        return builder->CreateICmpSGT(l, r);
    }
    return nullptr;
}

