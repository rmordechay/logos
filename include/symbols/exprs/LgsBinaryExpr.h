#pragma once
#include "data/LgsTokens.h"
#include "exprs/LgsExpr.h"

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsExpr* results = nullptr;
    LgsBinOpType op = NOOP;
    std::string opText = "";

    LgsBinaryExpr(LgsExpr* left, LgsExpr* right, const LgsBinOp op) : left(left), right(right), op(op.opType), opText(op.text) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
    ~LgsBinaryExpr() override;
};
