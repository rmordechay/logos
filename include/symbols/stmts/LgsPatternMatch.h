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
    BasicBlock* elseCase = nullptr;

    explicit LgsPatternMatch(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(LgsRuntime* runtime) override;
    ~LgsPatternMatch() override = default;
};


