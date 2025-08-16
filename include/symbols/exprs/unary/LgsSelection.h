#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsUnaryExpr;

class LgsSelection final : public LgsUnaryExpr {
public:
    std::vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    std::string pname() override;
    LgsExpr* lastExpr() const;
    Value* hashValue(LgsCodeGen* codeGen) override;
    void createIRValue(LgsCodeGen* codeGen) override;
    ~LgsSelection() override;
};


