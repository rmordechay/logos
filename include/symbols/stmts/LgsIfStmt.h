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
    void generateSimpleIf(LgsCodeGen* codeGen, Value* ifCondIR) const;
    void generateIfWithElse(LgsCodeGen* codeGen, Value* ifCondIR);
    void generateElseIf(LgsCodeGen* codeGen, Value* ifCondIR);
    void generatePatternMatching(LgsCodeGen* codeGen);
    static bool shouldBranch(Value* ifCondIR);
    ~LgsIfStmt() override;
};
