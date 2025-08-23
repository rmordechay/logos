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
    bool isPatternMatching = false;
    llvm::BasicBlock* IRExitBlock = nullptr;
    std::string tag;

    explicit LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock) : ifCond(ifCond), ifBlock(ifStmtBlock) {}
    json::value asJSON() override;
    ~LgsIfStmt() override;
};

class LgsPattern final : public LgsIfStmt {
public:
    explicit LgsPattern(LgsExpr* ifCond) : LgsIfStmt(ifCond, nullptr) {}
};