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
    llvm::Value* addIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* mulIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* subIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* divIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* inIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* modIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* eqIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* neIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* ltIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* gtIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* geIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* leIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* andIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* orIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* other) override;
    llvm::Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* other) override;
    std::string pname() override;
    ~LgsBinaryExpr() override;
};
