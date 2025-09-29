#pragma once
#include "LgsStmt.h"
#include "LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"

class LgsIfStmt : public LgsStmt {
public:
    LgsExpr* ifCond;
    LgsStmtsBlock* ifBlock;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> elseIfs;
    LgsStmtsBlock* elseBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;
    std::string tag;

    explicit LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock) : ifCond(ifCond), ifBlock(ifStmtBlock) {}
    json::value asJsonStr() override;
    ~LgsIfStmt() override;
};

class LgsPatternMatching final : public LgsStmt {
public:
    LgsExpr* cond;
    LgsStmtsBlock* elseBlock = nullptr;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> patterns;

    explicit LgsPatternMatching(LgsExpr* cond): cond(cond){}
    json::value asJsonStr() override;
    ~LgsPatternMatching() override;
};