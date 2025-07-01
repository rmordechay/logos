#pragma once
#include "LgsStmt.h"
#include "LgsStmtBlock.h"

#include <exprs/unary/LgsUnaryExpr.h>

class LgsPatternMatch final : public LgsStmt {
public:
    LgsExpr* expr;
    std::vector<LgsExpr*> patterns;
    std::vector<LgsStmtBlock*> patternsStmtBlocks;
    LgsStmtBlock* elseStmtBlock = nullptr;
    BasicBlock* exitBlock = nullptr;
    BasicBlock* defaultCase = nullptr;

    explicit LgsPatternMatch(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(LgsModule* runtime) override;
    ~LgsPatternMatch() override = default;
};


