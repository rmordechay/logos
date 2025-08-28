#pragma once
#include "LgsUnaryExpr.h"

enum LgsPostfixOperator {
    INC,
    DEC,
};

class LgsPostfixExpr final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* expr;
    LgsPostfixOperator op;

    LgsPostfixExpr(LgsUnaryExpr* baseExpr, const LgsPostfixOperator op) : expr(baseExpr), op(op) {}
    std::string pname() override;
    json::value asJSON() override;
    ~LgsPostfixExpr() override;
};
