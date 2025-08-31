#pragma once
#include "exprs/LgsExpr.h"


enum LgsPrefixOperator {
    NOT_PREFIX,
    MINUS_PREFIX,
    SQRT_PREFIX,
};

class LgsPrefixExpr final : public LgsExpr {
public:
    LgsExpr* expr;
    LgsPrefixOperator op;

    LgsPrefixExpr(LgsExpr* baseExpr, const LgsPrefixOperator op) : expr(baseExpr), op(op) {}
    json::value asJSON() override;
    std::string pname() override;
    ~LgsPrefixExpr() override;
};
