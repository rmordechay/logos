#pragma once
#include "exprs/LgsExpr.h"
#include "logos/LgsModule.h"
#include "LgsType.h"
#include <tuple>

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    Value* addIR(LgsModule* module, LgsExpr* other) override;
    Value* subIR(LgsModule* module, LgsExpr* other) override;
    Value* mulIR(LgsModule* module, LgsExpr* other) override;
    Value* divIR(LgsModule* module, LgsExpr* other) override;
    Value* modIR(LgsModule* module, LgsExpr* other) override;
    Value* eqIR(LgsModule* module, LgsExpr* other) override;
    Value* neIR(LgsModule* module, LgsExpr* other) override;
    Value* ltIR(LgsModule* module, LgsExpr* other) override;
    Value* gtIR(LgsModule* module, LgsExpr* other) override;
    Value* geIR(LgsModule* module, LgsExpr* other) override;
    Value* leIR(LgsModule* module, LgsExpr* other) override;
    tuple<Value*, Value*> loadExprs(LgsModule* module, LgsExpr* rExpr);
    virtual std::string getName();
    ~LgsUnaryExpr() override = default;
};

inline Value* LgsUnaryExpr::addIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateAdd(l, r);
}

inline Value* LgsUnaryExpr::subIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateSub(l, r);
}

inline Value* LgsUnaryExpr::mulIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateMul(l, r);
}

inline Value* LgsUnaryExpr::divIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateSDiv(l, r);
}

inline Value* LgsUnaryExpr::modIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateSRem(l, r);
}

inline Value* LgsUnaryExpr::eqIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateICmpEQ(l, r);
}

inline Value* LgsUnaryExpr::neIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateICmpNE(l, r);
}

inline Value* LgsUnaryExpr::ltIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateICmpSLT(l, r);
}

inline Value* LgsUnaryExpr::gtIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateICmpSGT(l, r);
}

inline Value* LgsUnaryExpr::geIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateICmpSGE(l, r);
}

inline Value* LgsUnaryExpr::leIR(LgsModule* module, LgsExpr* other) {
    auto [l, r] = loadExprs(module, other);
    return module->builder.CreateICmpSLE(l, r);
}

inline tuple<Value*, Value*> LgsUnaryExpr::loadExprs(LgsModule* module, LgsExpr* rExpr) {
    auto l = this->getIRValue(module);
    auto r = rExpr->getIRValue(module);
    if (l->getType()->isPointerTy()) {
        l = module->builder.CreateLoad(this->type->getIRType(module), l);
    }
    if (r->getType()->isPointerTy()) {
        r = module->builder.CreateLoad(rExpr->type->getIRType(module), r);
    }
    return tuple(l, r);
}
