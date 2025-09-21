#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

namespace llvm {
    class BasicBlock;
}

class LgsReturn final : public LgsStmt {
public:
    LgsExpr* expr = nullptr;
    BasicBlock* parentBlock = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    json::value asJSON() override;
    ~LgsReturn() override;
};




