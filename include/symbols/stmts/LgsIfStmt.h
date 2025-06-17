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
    void generateIfElse(LgsRuntime* runtime);
    void createIRStmt(LgsRuntime* runtime) override;
    void generateSimpleIf(LgsRuntime* runtime);
    void generateComplexIf(LgsRuntime* runtime);
    bool isBranchingNeeded(LgsRuntime* runtime, Value* ifCondIR) const;
    ~LgsIfStmt() override;
};




