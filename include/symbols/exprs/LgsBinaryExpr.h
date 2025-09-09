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
    json::value asJSON() override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* ltIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* gtIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* geIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* leIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* andIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* orIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* other) override;
    std::string pname() override;
    ~LgsBinaryExpr() override;
};
