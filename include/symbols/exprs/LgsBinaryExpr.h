#pragma once
#include "exprs/LgsExpr.h"

enum LgsOperator {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EQ,
    NE,
    LT,
    GT,
    GE,
    LE,
    AND,
    OR,
    BIT_AND,
    BIT_OR,
    BIT_XOR,
    LSHIFT,
    RSHIFT,
    IN,
    NOOP,
};

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    std::string opStr;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsOperator op) : LgsExpr(type), left(left), right(right), op(op) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    json::value asJsonStr() override;
    std::string pname() override;
    ~LgsBinaryExpr() override;
};
