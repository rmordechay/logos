#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsUnaryExpr;

class LgsSelection final : public LgsUnaryExpr {
public:
    std::vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {
        isAssignable = true;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* lastExpr() const;
    LgsExpr* lastExprParent() const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    std::string pname() override;
    Value* hash(LgsLLVMGen& cg) override;
    json::value asJSON() override;
    ~LgsSelection() override;
};
