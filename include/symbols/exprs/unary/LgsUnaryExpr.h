#pragma once
#include "exprs/LgsExpr.h"
#include "logos/LgsModule.h"
#include "LgsType.h"

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    string prettyName() override;
    Value* addIR(LgsModule* runtime, LgsExpr* other) override;
    Value* subIR(LgsModule* runtime, LgsExpr* other) override;
    Value* mulIR(LgsModule* runtime, LgsExpr* other) override;
    Value* divIR(LgsModule* runtime, LgsExpr* other) override;
    Value* modIR(LgsModule* runtime, LgsExpr* other) override;
    Value* eqIR(LgsModule* runtime, LgsExpr* other) override;
    Value* neIR(LgsModule* runtime, LgsExpr* other) override;
    Value* ltIR(LgsModule* runtime, LgsExpr* other) override;
    Value* gtIR(LgsModule* runtime, LgsExpr* other) override;
    Value* geIR(LgsModule* runtime, LgsExpr* other) override;
    Value* leIR(LgsModule* runtime, LgsExpr* other) override;
    tuple<Value*, Value*> loadExprs(LgsModule* runtime, LgsExpr* rExpr);
    virtual std::string getExprName();
    ~LgsUnaryExpr() override = default;
};

inline std::string LgsUnaryExpr::getExprName() {
    assert(false);
}

inline string LgsUnaryExpr::prettyName() {
    return getExprName();
}

inline Value* LgsUnaryExpr::addIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateAdd(l, r);
}

inline Value* LgsUnaryExpr::subIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateSub(l, r);
}

inline Value* LgsUnaryExpr::mulIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateMul(l, r);
}

inline Value* LgsUnaryExpr::divIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateSDiv(l, r);
}

inline Value* LgsUnaryExpr::modIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateSRem(l, r);
}

inline Value* LgsUnaryExpr::eqIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateICmpEQ(l, r);
}

inline Value* LgsUnaryExpr::neIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateICmpNE(l, r);
}

inline Value* LgsUnaryExpr::ltIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateICmpSLT(l, r);
}

inline Value* LgsUnaryExpr::gtIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateICmpSGT(l, r);
}

inline Value* LgsUnaryExpr::geIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateICmpSGE(l, r);
}

inline Value* LgsUnaryExpr::leIR(LgsModule* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateICmpSLE(l, r);
}

inline tuple<Value*, Value*> LgsUnaryExpr::loadExprs(LgsModule* runtime, LgsExpr* rExpr) {
    auto l = this->getIRValue(runtime);
    auto r = rExpr->getIRValue(runtime);
    if (l->getType()->isPointerTy()) {
        l = runtime->builder.CreateLoad(this->type->getIRType(runtime->context), l);
    }
    if (r->getType()->isPointerTy()) {
        r = runtime->builder.CreateLoad(rExpr->type->getIRType(runtime->context), r);
    }
    return tuple(l, r);
}
