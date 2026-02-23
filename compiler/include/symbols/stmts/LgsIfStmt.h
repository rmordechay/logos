#pragma once
#include <string>
#include <utility>
#include <vector>

#include "LgsStmt.h"
#include "LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "LgsValue.h"

class LgsExpr;
namespace llvm {
class BasicBlock;
}

class LgsIfStmt final : public LgsStmt {
public:
    LgsExpr* ifCond;
    LgsStmtsBlock* ifBlock = new LgsStmtsBlock();
    LgsStmtsBlock* elseBlock = nullptr;
    LgsStmtsBlock* macroTrueBlock = nullptr;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> elseIfs;
    BasicBlock* IRExitBlock = nullptr;
    bool isSwitchBool = false;
    std::string tag;

    explicit LgsIfStmt(LgsExpr* ifCond, LgsStmtsBlock* ifStmtBlock) : ifCond(ifCond), ifBlock(ifStmtBlock) {}
    explicit LgsIfStmt(LgsExpr* ifCond) : ifCond(ifCond) {}
    void setDebugValue(LgsCodeGen& cg) override;
    LgsStmt* clone() override;
    ~LgsIfStmt() override;
};
