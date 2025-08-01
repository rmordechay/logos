#pragma once
#include "LgsStmt.h"
#include "LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"

class LgsIfStmt final : public LgsStmt {
public:
    LgsExpr* ifCond;
    LgsStmtsBlock* ifBlock;
    vector<std::pair<LgsExpr*, LgsStmtsBlock*>> elseIfs;
    LgsStmtsBlock* elseBlock = nullptr;
    bool isPatternMatching = false;
    string tag;

    explicit LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock = nullptr) : ifCond(ifCond), ifBlock(ifStmtBlock) {}
    void createIRStmt(LgsCodeGen* codeGen) override;
    void generateIfElse(LgsCodeGen* codeGen);
    void generateSimpleIf(LgsCodeGen* codeGen);
    void generateComplexIf(LgsCodeGen* codeGen);
    void generatePatternMatching(LgsCodeGen* codeGen);
    bool shouldBranch(LgsCodeGen* codeGen, Value* ifCondIR) const;
    ~LgsIfStmt() override;
};
