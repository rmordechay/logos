#pragma once
#include "LgsStmt.h"
#include "LgsStmtsBlock.h"

#include <exprs/unary/LgsUnaryExpr.h>

class LgsPatternMatch final : public LgsStmt {
public:
    LgsExpr* expr;
    std::vector<LgsExpr*> patterns;
    std::vector<LgsStmtsBlock*> patternsStmtBlocks;
    LgsStmtsBlock* elseStmtBlock = nullptr;
    BasicBlock* exitBlock = nullptr;
    BasicBlock* defaultCase = nullptr;

    explicit LgsPatternMatch(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(LgsModule* module) override;
    ~LgsPatternMatch() override = default;
};


