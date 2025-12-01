#pragma once
#include "LgsBinaryTokens.h"
#include "LgsTokens.h"
#include "exprs/LgsExpr.h"

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsExpr* results = nullptr;
    LgsBinOp op = LgsBinOp(NOOP, "");

    LgsBinaryExpr(LgsExpr* left, LgsExpr* right, const LgsBinOp& op) : left(left), right(right), op(op) {}
    Value* loadIR(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    ~LgsBinaryExpr() override;
};
