#include "exprs/LogosBinaryExpr.h"

Value* LogosBinaryExpr::computeIRValue(CodeGenMetadata* metadata) {
    const auto l = left->writeIRValue(metadata);
    const auto r = right->writeIRValue(metadata);
    auto& builder = metadata->builder;
    if (op == PLUS) {
        return builder.CreateAdd(l, r);
    }
    if (op == MINUS) {
        return builder.CreateSub(l, r);
    }
    if (op == STAR) {
        return builder.CreateMul(l, r);
    }
    if (op == RANGLE) {
        return builder.CreateICmpSGT(l, r);
    }
    if (op == LANGLE) {
        return builder.CreateICmpSLT(l, r);
    }
    return nullptr;
}

