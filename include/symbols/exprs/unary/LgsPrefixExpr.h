#pragma once
#include "LgsUnaryExpr.h"

enum LgsPrefixOperator {
    NOT_PREFIX,
    MINUS_PREFIX,
    SQRT_PREFIX,
};

class LgsPrefixExpr final : public LgsUnaryExpr {
public:
    LgsExpr* expr;
    LgsPrefixOperator op;

    LgsPrefixExpr(LgsExpr* baseExpr, const LgsPrefixOperator op) : expr(baseExpr), op(op) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    std::string pname() override;
    ~LgsPrefixExpr() override;
};
