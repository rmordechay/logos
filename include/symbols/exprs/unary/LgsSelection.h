#pragma once
#include "LgsAssignable.h"
#include "exprs/unary/LgsUnaryExpr.h"

class LgsUnaryExpr;

class LgsSelection final : public LgsUnaryExpr, public LgsAssignable {
public:
    std::vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    Value* loadIR(LgsLLVM& codeGen) override;
    LgsExpr* lastExpr() const;
    LgsExpr* lastExprParent() const;
    void assign(LgsLLVM& codeGen, LgsExpr* expr) override;
    std::string pname() override;
    Value* hash(LgsLLVM& codeGen) override;
    json::value asJSON() override;
    ~LgsSelection() override;
};


