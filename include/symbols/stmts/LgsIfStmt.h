#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
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
    std::vector<LgsExpr*> elseIfConds;
    LgsStmtBlock* ifStmtBlock;
    std::vector<LgsStmtBlock*> elseIfStmtBlocks;
    LgsStmtBlock* elseStmtBlock = nullptr;
    BasicBlock* IRIfTrueBlock = nullptr;
    BasicBlock* IRIfEndBlock = nullptr;
    BasicBlock* IRElseBlock = nullptr;
    BasicBlock* IRElseIfStartBlock = nullptr;
    BasicBlock* IRElseIfCheckBlock = nullptr;

    LgsIfStmt(LgsExpr* ifCond, LgsStmtBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    void createIRStmt(LgsRuntime* runtime) override;
    void computeSimpleIf(LgsRuntime* runtime);
    void computeComplexIf(LgsRuntime* runtime);
    void createElseIfBlocks(LgsRuntime* runtime);
    void createElseBlock(LgsRuntime* runtime, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const;
    ~LgsIfStmt() override;
};



#endif //LOGOSIFSTMT_H
