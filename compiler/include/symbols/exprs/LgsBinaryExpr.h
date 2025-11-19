#pragma once
#include "LgsTokens.h"
#include "exprs/LgsExpr.h"

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsExpr* results = nullptr;
    LgsBinOp op = LgsBinOp(NOOP, "");

    LgsBinaryExpr(LgsExpr* left, LgsExpr* right, const LgsBinOp& op) : left(left), right(right), op(op) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
    void setDebugValue(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsBinaryExpr() override;
};
