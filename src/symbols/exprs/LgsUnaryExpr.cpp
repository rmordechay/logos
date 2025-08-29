#include "exprs/unary/LgsUnaryExpr.h"
#include "LgsType.h"
#include "codegen/LgsLLVMGen.h"


Value* LgsUnaryExpr::addIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    if (l->getType()->isFloatingPointTy()) return cg.builder.CreateFAdd(l, r);
    return cg.builder.CreateAdd(l, r);
}

Value* LgsUnaryExpr::subIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    if (l->getType()->isFloatingPointTy()) return cg.builder.CreateFSub(l, r);
    return cg.builder.CreateSub(l, r);
}

Value* LgsUnaryExpr::mulIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    if (l->getType()->isFloatingPointTy()) return cg.builder.CreateFMul(l, r);
    return cg.builder.CreateMul(l, r);
}

Value* LgsUnaryExpr::divIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    if (l->getType()->isFloatingPointTy()) return cg.builder.CreateFDiv(l, r);
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsUnaryExpr::inIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::modIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    return cg.builder.CreateSRem(l, r);
}

Value* LgsUnaryExpr::eqIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    return cg.builder.CreateICmpEQ(l, r);
}

Value* LgsUnaryExpr::neIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    return cg.builder.CreateICmpNE(l, r);
}

Value* LgsUnaryExpr::ltIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    return cg.builder.CreateICmpSLT(l, r);
}

Value* LgsUnaryExpr::gtIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    return cg.builder.CreateICmpSGT(l, r);
}

Value* LgsUnaryExpr::geIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    return cg.builder.CreateICmpSGE(l, r);
}

Value* LgsUnaryExpr::leIR(LgsLLVMGen& cg, LgsExpr* other) {
    auto [l, r] = loadExprs(&cg, other);
    return cg.builder.CreateICmpSLE(l, r);
}

Value* LgsUnaryExpr::andIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::orIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitAndIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitOrIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitXorIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::rshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::lshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

std::pair<Value*, Value*> LgsUnaryExpr::loadExprs(LgsLLVMGen* cg, LgsExpr* rExpr) {
    auto l = this->IRValue;
    auto r = rExpr->IRValue;
    if (l->getType()->isPointerTy()) {
        l = cg->builder.CreateLoad(type->getIRType(*cg), l);
    }
    if (r->getType()->isPointerTy()) {
        r = cg->builder.CreateLoad(rExpr->type->getIRType(*cg), r);
    }
    return std::pair(l, r);
}
