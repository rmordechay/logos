#include "exprs/unary/LgsUnaryExpr.h"
#include "LgsType.h"
#include "codegen/LgsLLVM.h"


Value* LgsUnaryExpr::addIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    if (l->getType()->isFloatingPointTy()) return codeGen.builder.CreateFAdd(l, r);
    return codeGen.builder.CreateAdd(l, r);
}

Value* LgsUnaryExpr::subIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    if (l->getType()->isFloatingPointTy()) return codeGen.builder.CreateFSub(l, r);
    return codeGen.builder.CreateSub(l, r);
}

Value* LgsUnaryExpr::mulIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    if (l->getType()->isFloatingPointTy()) return codeGen.builder.CreateFMul(l, r);
    return codeGen.builder.CreateMul(l, r);
}

Value* LgsUnaryExpr::divIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    if (l->getType()->isFloatingPointTy()) return codeGen.builder.CreateFDiv(l, r);
    return codeGen.builder.CreateSDiv(l, r);
}

Value* LgsUnaryExpr::inIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::modIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    return codeGen.builder.CreateSRem(l, r);
}

Value* LgsUnaryExpr::eqIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    return codeGen.builder.CreateICmpEQ(l, r);
}

Value* LgsUnaryExpr::neIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    return codeGen.builder.CreateICmpNE(l, r);
}

Value* LgsUnaryExpr::ltIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    return codeGen.builder.CreateICmpSLT(l, r);
}

Value* LgsUnaryExpr::gtIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    return codeGen.builder.CreateICmpSGT(l, r);
}

Value* LgsUnaryExpr::geIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    return codeGen.builder.CreateICmpSGE(l, r);
}

Value* LgsUnaryExpr::leIR(LgsLLVM& codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(&codeGen, other);
    return codeGen.builder.CreateICmpSLE(l, r);
}

Value* LgsUnaryExpr::andIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::orIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitAndIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitOrIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitXorIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::rshiftIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::lshiftIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

std::pair<Value*, Value*> LgsUnaryExpr::loadExprs(LgsLLVM* codeGen, LgsExpr* rExpr) {
    auto l = this->IRValue;
    auto r = rExpr->IRValue;
    if (l->getType()->isPointerTy()) {
        l = codeGen->builder.CreateLoad(type->getIRType(*codeGen), l);
    }
    if (r->getType()->isPointerTy()) {
        r = codeGen->builder.CreateLoad(rExpr->type->getIRType(*codeGen), r);
    }
    return std::pair(l, r);
}
