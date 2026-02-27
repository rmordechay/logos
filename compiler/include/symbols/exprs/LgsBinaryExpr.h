#pragma once
#include <string>

#include "LgsBinaryTokens.h"
#include "exprs/LgsExpr.h"

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsBinOp op = LgsBinOp(NOOP, "");

    LgsBinaryExpr(LgsExpr* left, LgsExpr* right, const LgsBinOp& op) : left(left), right(right), op(op) {}
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
    LgsExpr* clone() const override;
    ~LgsBinaryExpr() override;
};
