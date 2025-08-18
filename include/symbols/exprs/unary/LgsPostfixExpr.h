#pragma once
#include "LgsUnaryExpr.h"
#include "stmts/LgsStmt.h"

enum LgsPostfixOperator {
    INC,
    DEC,
};

class LgsPostfixExpr final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* expr;
    LgsPostfixOperator op;

    LgsPostfixExpr(LgsUnaryExpr* baseExpr, const LgsPostfixOperator op) : expr(baseExpr), op(op) {}
    Value* IncOrDecValue(LgsCodeGen* codeGen) const;
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
    json::value_ref asJSON() override;
    ~LgsPostfixExpr() override;
};
