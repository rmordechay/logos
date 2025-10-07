#pragma once
#include "LgsStmt.h"
#include "LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"

class LgsIfStmt final : public LgsStmt {
public:
    LgsExpr* ifCond;
    LgsStmtsBlock* ifBlock = new LgsStmtsBlock();
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> elseIfs;
    LgsStmtsBlock* elseBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;
    std::string tag;

    explicit LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock) : ifCond(ifCond), ifBlock(ifStmtBlock) {}
    explicit LgsIfStmt(LgsExpr* ifCond) : ifCond(ifCond) {}
    void parseAsJSON(std::stringstream& json) override;
    ~LgsIfStmt() override;
};

class LgsPatternMatch final : public LgsStmt {
public:
    LgsExpr* cond;
    LgsStmtsBlock* elseBlock = nullptr;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> patterns;
    bool isBoolMatch = false;

    explicit LgsPatternMatch(LgsExpr* cond = nullptr): cond(cond){}
    ~LgsPatternMatch() override;
};