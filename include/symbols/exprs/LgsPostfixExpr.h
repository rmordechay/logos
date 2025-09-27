#pragma once
#include "exprs/LgsExpr.h"


enum LgsPostfixOperator {
    INC,
    DEC,
};

class LgsPostfixExpr final : public LgsExpr {
public:
    LgsExpr* expr;
    LgsPostfixOperator op;

    LgsPostfixExpr(LgsExpr* baseExpr, const LgsPostfixOperator op) : expr(baseExpr), op(op) {}
    std::string getName() override;
    json::value asJsonStr() override;
    ~LgsPostfixExpr() override;
};
