#pragma once
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "logos/LgsCodeGen.h"

class LgsUnaryExpr : public LgsExpr {
public:

    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* subIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* mulIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* divIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* modIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* neIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* ltIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* gtIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* geIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* leIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    std::tuple<Value*, Value*> loadExprs(LgsCodeGen* codeGen, LgsExpr* rExpr);
    ~LgsUnaryExpr() override = default;
};

inline Value* LgsUnaryExpr::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateAdd(l, r);
}

inline Value* LgsUnaryExpr::subIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateSub(l, r);
}

inline Value* LgsUnaryExpr::mulIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateMul(l, r);
}

inline Value* LgsUnaryExpr::divIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateSDiv(l, r);
}

inline Value* LgsUnaryExpr::modIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateSRem(l, r);
}

inline Value* LgsUnaryExpr::eqIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpEQ(l, r);
}

inline Value* LgsUnaryExpr::neIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpNE(l, r);
}

inline Value* LgsUnaryExpr::ltIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSLT(l, r);
}

inline Value* LgsUnaryExpr::gtIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSGT(l, r);
}

inline Value* LgsUnaryExpr::geIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSGE(l, r);
}

inline Value* LgsUnaryExpr::leIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateICmpSLE(l, r);
}

inline Value* LgsUnaryExpr::andIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateLogicalAnd(l, r);
}

inline Value* LgsUnaryExpr::orIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateLogicalOr(l, r);
}

inline Value* LgsUnaryExpr::bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateAnd(l, r);
}

inline Value* LgsUnaryExpr::bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateOr(l, r);
}

inline Value* LgsUnaryExpr::bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateXor(l, r);
}

inline Value* LgsUnaryExpr::rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateShl(l, r);
}

inline Value* LgsUnaryExpr::lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    auto [l, r] = loadExprs(codeGen, other);
    return codeGen->builder.CreateAShr(l, r);
}

inline std::tuple<Value*, Value*> LgsUnaryExpr::loadExprs(LgsCodeGen* codeGen, LgsExpr* rExpr) {
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
