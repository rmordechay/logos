#pragma once
#include "LgsUnaryExpr.h"
#include "stmts/LgsStmt.h"

enum LgsPrefixOperator {
    NOT_PREFIX,
    MINUS_PREFIX,
};

class LgsPrefixExpr final : public LgsUnaryExpr {
public:

    LgsExpr* expr;
    LgsPrefixOperator op;

    LgsPrefixExpr(LgsExpr* baseExpr, const LgsPrefixOperator op) : expr(baseExpr), op(op) {}
    std::string prettyName() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    ~LgsPrefixExpr() override = default;
};
