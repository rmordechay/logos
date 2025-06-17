#pragma once
#include "LgsStmt.h"
#include "LgsStmtBlock.h"
#include "exprs/LgsExpr.h"

#define BB_IF_TRUE "if_true"
#define BB_IF_END "if_end"
#define BB_ELSE "else"
#define BB_ELSE_IF_START "else_if_start"
#define BB_ELSE_IF_CHECK "else_if_check"

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
    void generateSimpleIf(LgsRuntime* runtime) const;
    void generateComplexIf(LgsRuntime* runtime);
    bool isBranchingNeeded(LgsRuntime* runtime, Value* ifCondIR) const;
    ~LgsIfStmt() override;
};




