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
    Value* IncOrDecValue(LgsModule* module) const;
    Value* createIRValue(LgsModule* module) override;
    void createIRStmt(LgsModule* module) override;
    ~LgsPostfixExpr() override = default;
};
