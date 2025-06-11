#pragma once
#include "LgsUnaryExpr.h"
#include "stmts/LgsStmt.h"

enum LgsPostfixOperator {
    INC,
    DEC,
};

class LgsPostfixExpr final : public LgsStmt, public LgsUnaryExpr {
public:
    LgsUnaryExpr* expr;
    LgsPostfixOperator op;

    LgsPostfixExpr(LgsUnaryExpr* baseExpr, const LgsPostfixOperator op) : expr(baseExpr), op(op) {}
    Value* IncOrDec(LgsRuntime* runtime) const;
    Value* createIRValue(LgsRuntime* runtime) override;
    void createIRStmt(LgsRuntime* runtime) override;
    ~LgsPostfixExpr() override = default;
};
