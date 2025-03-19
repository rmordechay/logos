#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LgsStmt.h"
#include "LgsStmtBlock.h"
#include "exprs/LgsExpr.h"

#define BB_IF_START "if_start"
#define BB_IF_END "if_end"
#define BB_ELSE "else"
#define BB_ELSE_IF_START "else_if_start"
#define BB_ELSE_IF_CHECK "else_if_check"

class LgsIf final : public LgsStmt {
public:
    LgsExpr* ifCond;
    LgsStmtBlock* ifStmtBlock;
    vector<LgsExpr*> elseIfConds;
    vector<LgsStmtBlock*> elseIfStmtBlocks;
    LgsStmtBlock* elseStmtBlock = nullptr;

    LgsIf(LgsExpr* ifCond, LgsStmtBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void computeSimpleIf(CodeGenMetadata* metadata);
    void createElseBlock(CodeGenMetadata* metadata, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const;
    void computeComplexIf(CodeGenMetadata* metadata);
    ~LgsIf() override;
};



#endif //LOGOSIFSTMT_H
