#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;
    BasicBlock* parentBlock = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(LgsCodeGen* codeGen) override;
    ~LgsReturn() override;
};




