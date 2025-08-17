#include "exprs/unary/LgsUnaryExpr.h"

#include "LgsType.h"
#include "logos/LgsCodeGen.h"


Value* LgsUnaryExpr::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateAdd(l, r);
}

Value* LgsUnaryExpr::subIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateSub(l, r);
}

Value* LgsUnaryExpr::mulIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateMul(l, r);
}

Value* LgsUnaryExpr::divIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateSDiv(l, r);
}

Value* LgsUnaryExpr::modIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateSRem(l, r);
}

Value* LgsUnaryExpr::eqIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpEQ(l, r);
}

Value* LgsUnaryExpr::neIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpNE(l, r);
}

Value* LgsUnaryExpr::ltIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSLT(l, r);
}

Value* LgsUnaryExpr::gtIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSGT(l, r);
}

Value* LgsUnaryExpr::geIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSGE(l, r);
}

Value* LgsUnaryExpr::leIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSLE(l, r);
}

Value* LgsUnaryExpr::andIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::orIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUnaryExpr::lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

std::tuple<Value*, Value*> LgsUnaryExpr::loadExprs(LgsCodeGen* codeGen, LgsExpr* rExpr) {
    auto l = this->getIRValue(codeGen);
    auto r = rExpr->getIRValue(codeGen);
    if (l->getType()->isPointerTy()) {
        l = codeGen->builder.CreateLoad(type->getIRType(codeGen), l);
    }
    if (r->getType()->isPointerTy()) {
        r = codeGen->builder.CreateLoad(rExpr->type->getIRType(codeGen), r);
    }
    return std::tuple(l, r);
}
