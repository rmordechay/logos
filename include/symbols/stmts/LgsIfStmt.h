#pragma once
#include "LgsStmt.h"
#include "LgsStmtBlock.h"
#include "exprs/LgsExpr.h"

class LgsIfStmt final : public LgsStmt {
public:
    LgsExpr* ifCond;
    vector<LgsExpr*> elseIfConds;
    LgsStmtBlock* ifStmtBlock;
    vector<LgsStmtBlock*> elseIfStmtBlocks;
    LgsStmtBlock* elseStmtBlock = nullptr;
    BasicBlock* endBlock = nullptr;
    string tag;

    LgsIfStmt(LgsExpr* ifCond, LgsStmtBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    void generateIfElse(LgsModule* module);
    void createIRStmt(LgsModule* module) override;
    void generateSimpleIf(LgsModule* module);
    void generateComplexIf(LgsModule* module);
    bool needsBranching(LgsModule* module, Value* ifCondIR) const;
    ~LgsIfStmt() override;
};




