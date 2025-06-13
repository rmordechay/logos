#pragma once
#include "exprs/LgsExpr.h"
#include "logos/LgsRuntime.h"
#include "LgsType.h"

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* subIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* mulIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* divIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* modIR(LgsRuntime* runtime, LgsExpr* other) override;
    tuple<Value*, Value*> loadExprs(LgsRuntime* runtime, LgsExpr* rExpr);
    virtual std::string getName();
    ~LgsUnaryExpr() override = default;
};

inline std::string LgsUnaryExpr::getName() {
    assert(false);
}

inline Value* LgsUnaryExpr::addIR(LgsRuntime* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateAdd(l, r);
}

inline Value* LgsUnaryExpr::subIR(LgsRuntime* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateSub(l, r);
}

inline Value* LgsUnaryExpr::mulIR(LgsRuntime* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateMul(l, r);
}

inline Value* LgsUnaryExpr::divIR(LgsRuntime* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateSDiv(l, r);
}

inline Value* LgsUnaryExpr::modIR(LgsRuntime* runtime, LgsExpr* other) {
    auto [l, r] = loadExprs(runtime, other);
    return runtime->builder.CreateSRem(l, r);
}

inline tuple<Value*, Value*> LgsUnaryExpr::loadExprs(LgsRuntime* runtime, LgsExpr* rExpr) {
    auto l = this->getIRValue(runtime);
    auto r = rExpr->getIRValue(runtime);
    if (l->getType()->isPointerTy()) {
        l = runtime->builder.CreateLoad(this->type->getIRType(), l);
    }
    if (r->getType()->isPointerTy()) {
        r = runtime->builder.CreateLoad(rExpr->type->getIRType(), r);
    }
    return tuple(l, r);
}
