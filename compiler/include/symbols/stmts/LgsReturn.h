#pragma once
#include "LgsStmt.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr* expr = nullptr;
    BasicBlock* parentBlock = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsReturn() override;
};




