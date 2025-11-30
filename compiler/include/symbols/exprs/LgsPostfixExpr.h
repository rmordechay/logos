#pragma once
#include "exprs/LgsExpr.h"

enum LgsPostfixOperator {
    INC,
    DEC,
};

class LgsPostfixExpr final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsPostfixOperator op;

    LgsPostfixExpr(LgsExpr* baseExpr, const LgsPostfixOperator op) : baseExpr(baseExpr), op(op) {}
    std::string asText() override;
    ~LgsPostfixExpr() override;
};
