#pragma once
#include "LgsStmt.h"
#include "LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"

class LgsIfStmt final : public LgsStmt {
public:
    LgsExpr* ifCond;
    vector<LgsExpr*> elseIfConds;
    LgsStmtsBlock* ifStmtsBlock;
    vector<LgsStmtsBlock*> elseIfStmtsBlocks;
    LgsStmtsBlock* elseStmtsBlock = nullptr;
    bool isPatternMatching = false;
    string tag;

    explicit LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock = nullptr) : ifCond(ifCond), ifStmtsBlock(ifStmtBlock) {}
    void createIRStmt(LgsCodeGen* codeGen) override;
    void generateIfElse(LgsCodeGen* codeGen) const;
    void generateSimpleIf(LgsCodeGen* codeGen) const;
    void generateComplexIf(LgsCodeGen* codeGen) const;
    void generatePatternMatching(LgsCodeGen* codeGen) const;
    bool shouldBranch(LgsCodeGen* codeGen, Value* ifCondIR) const;
    ~LgsIfStmt() override;
};




