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
    llvm::Value* addIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* mulIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* subIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* divIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* inIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* modIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* eqIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* neIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* ltIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* gtIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* geIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* leIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* andIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* orIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* bitAndIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* bitOrIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* bitXorIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* rshiftIR(LgsLLVM& codeGen, LgsExpr* other) override;
    llvm::Value* lshiftIR(LgsLLVM& codeGen, LgsExpr* other) override;
    std::string pname() override;
    ~LgsBinaryExpr() override;
};
