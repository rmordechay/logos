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
    Value* createIRValue(LgsCodeGen* codeGen) override;
    Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* mulIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* subIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* divIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* modIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* neIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* ltIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* gtIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* geIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* leIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    ~LgsBinaryExpr() override = default;
};


