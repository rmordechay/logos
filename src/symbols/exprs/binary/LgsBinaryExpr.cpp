#include "binary/LgsBinaryExpr.h"

Value* LgsBinaryExpr::createIRValue(CodeGenMetadata* metadata) {
    const auto l = left->getIRValue(metadata);
    const auto r = right->getIRValue(metadata);
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
    if (op == SLASH) {
        return builder.CreateSDiv(l, r);
    }
    if (op == RANGLE) {
        return builder.CreateICmpSGT(l, r);
    }
    if (op == LANGLE) {
        return builder.CreateICmpSLT(l, r);
    }
    if (op == DOUBLE_EQUAL) {
        return builder.CreateICmpEQ(l, r);
    }
    if (op == NOT_EQUAL) {
        return builder.CreateICmpNE(l, r);
    }
    if (op == LE) {
        return builder.CreateICmpSLE(l, r);
    }
    if (op == GE) {
        return builder.CreateICmpSGE(l, r);
    }
    return nullptr;
}

