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
    LgsStmtBlock* ifStmtBlock;
    std::vector<LgsExpr*> elseIfConds;
    std::vector<LgsStmtBlock*> elseIfStmtBlocks;
    LgsStmtBlock* elseStmtBlock = nullptr;
    bool hasReturn = false;

    BasicBlock* ifTrueBlock = nullptr;
    BasicBlock* ifEndBlock = nullptr;
    BasicBlock* elseBlock = nullptr;
    BasicBlock* elseIfStartBlock = nullptr;
    BasicBlock* elseIfCheckBlock = nullptr;

    LgsIfStmt(LgsExpr* ifCond, LgsStmtBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    void createIRStmt(Module* module, LgsRuntime* runtime) override;
    void computeSimpleIf(Module* module, LgsRuntime* runtime);
    void computeComplexIf(Module* module, LgsRuntime* runtime);
    void createElseIfBlocks(Module* module, LgsRuntime* runtime);
    void createElseBlock(Module* module, LgsRuntime* runtime, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const;
    ~LgsIfStmt() override;
};



#endif //LOGOSIFSTMT_H
