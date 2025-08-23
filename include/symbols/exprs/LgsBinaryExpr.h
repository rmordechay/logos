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
    llvm::Value* addIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* mulIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* subIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* divIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* inIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* modIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* eqIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* neIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* ltIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* gtIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* geIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* leIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* andIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* orIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* bitAndIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* bitOrIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* bitXorIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* rshiftIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    llvm::Value* lshiftIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    std::string pname() override;
    ~LgsBinaryExpr() override;
};
