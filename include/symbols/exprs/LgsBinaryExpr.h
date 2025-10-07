#pragma once
#include "exprs/LgsExpr.h"

enum LgsBinOpType {
    ADD,
    SUB,
    MUL,
    DIV,
    MODULO,
    BIT_AND,
    BIT_OR,
    BIT_XOR,
    LSHIFT,
    RSHIFT,
    EQ,
    NE,
    LT,
    GT,
    GE,
    LE,
    AND,
    OR,
    IN,
    NOOP,
};

struct LgsBinOp {
    LgsBinOpType opType;
    std::string name;
};

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsBinOp op = LgsBinOp{NOOP, ""};

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsBinOp& op) : LgsExpr(type), left(left), right(right), op(op) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    void parseAsJSON(std::stringstream& json) override;
    std::string getName() override;
    ~LgsBinaryExpr() override;
};
