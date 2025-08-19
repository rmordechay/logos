#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsUnaryExpr;

class LgsSelection final : public LgsUnaryExpr {
public:
    std::vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    LgsExpr* lastExpr() const;
    LgsExpr* lastExprParent() const;
    std::string pname() override;
    Value* hash(LgsCodeGen* codeGen) override;
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    ~LgsSelection() override;
};


