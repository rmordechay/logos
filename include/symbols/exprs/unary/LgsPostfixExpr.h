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
    Value* IncOrDecValue(LgsModule* runtime) const;
    Value* createIRValue(LgsModule* runtime) override;
    void createIRStmt(LgsModule* runtime) override;
    ~LgsPostfixExpr() override = default;
};
