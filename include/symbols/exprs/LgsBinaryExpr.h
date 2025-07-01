#pragma once
#include "exprs/LgsExpr.h"

enum LgsOperator {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NE,
    EQ,
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
    NOOP,
};

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    string opStr;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsOperator op) : LgsExpr(type), left(left), right(right), op(op) {}
    string prettyName() override;
    Value* createIRValue(LgsModule* runtime) override;
    Value* addIR(LgsModule* runtime, LgsExpr* other) override;
    Value* mulIR(LgsModule* runtime, LgsExpr* other) override;
    Value* subIR(LgsModule* runtime, LgsExpr* other) override;
    Value* divIR(LgsModule* runtime, LgsExpr* other) override;
    ~LgsBinaryExpr() override = default;
};


