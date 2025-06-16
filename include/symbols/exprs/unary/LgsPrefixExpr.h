#pragma once
#include "LgsUnaryExpr.h"
#include "stmts/LgsStmt.h"

enum LgsPrefixOperator {
    NOT_PREFIX,
    MINUS_PREFIX,
};

class LgsPrefixExpr final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* expr;
    LgsPrefixOperator op;

    LgsPrefixExpr(LgsUnaryExpr* baseExpr, const LgsPrefixOperator op) : expr(baseExpr), op(op) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsPrefixExpr() override = default;
};
