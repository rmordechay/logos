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
    BasicBlock* endBlock = nullptr;
    string tag;

    LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    void generateIfElse(LgsModule* module);
    void createIRStmt(LgsModule* module) override;
    void generateSimpleIf(LgsModule* module);
    void generateComplexIf(LgsModule* module);
    bool needsBranching(LgsModule* module, Value* ifCondIR) const;
    ~LgsIfStmt() override;
};




