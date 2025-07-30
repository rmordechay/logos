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
    Value* IncOrDecValue(LgsCodeGen* codeGen) const;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    string prettyName() override;
    void createIRStmt(LgsCodeGen* codeGen) override;
    ~LgsPostfixExpr() override = default;
};
