#pragma once
#include "LgsStmt.h"
#include "LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"

class LgsIfStmt final : public LgsStmt {
public:
    LgsExpr* ifCond;
    vector<LgsExpr*> elseIfConds;
    LgsStmtsBlock* ifStmtBlock;
    vector<LgsStmtsBlock*> elseIfStmtBlocks;
    LgsStmtsBlock* elseStmtBlock = nullptr;
    string tag;

    LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    void generateIfElse(LgsModule* module) const;
    void createIRStmt(LgsModule* module) override;
    void generateSimpleIf(LgsModule* module) const;
    void generateComplexIf(LgsModule* module) const;
    bool shouldBranch(LgsModule* module, Value* ifCondIR) const;
    ~LgsIfStmt() override;
};




