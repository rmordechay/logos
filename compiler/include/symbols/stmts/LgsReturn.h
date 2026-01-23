#pragma once
#include "LgsStmt.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr* expr = nullptr;
    BasicBlock* parentBlock = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void setDebugValue(LgsCodeGen& cg) override;
    LgsStmt* clone() override;
    ~LgsReturn() override;
};




