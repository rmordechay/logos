#pragma once
#include "LgsStmt.h"
#include "LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"

class LgsIfStmt final : public LgsStmt {
public:
    LgsExpr* ifCond;
    LgsStmtsBlock* ifBlock;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> elseIfs;
    LgsStmtsBlock* elseBlock = nullptr;
    bool isPatternMatching = false;
    llvm::BasicBlock* IRExitBlock = nullptr;
    std::string tag;

    explicit LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock = nullptr) : ifCond(ifCond), ifBlock(ifStmtBlock) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    void generateSimpleIf(LgsCodeGen* codeGen);
    void generateIfWithElse(LgsCodeGen* codeGen);
    void generateElseIf(LgsCodeGen* codeGen);
    void generatePatternMatching(LgsCodeGen* codeGen);
    json::value asJSON() override;
    ~LgsIfStmt() override;
};
