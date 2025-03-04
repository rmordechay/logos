#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LogosStmt.h"
#include "LogosStmtBlock.h"
#include "exprs/LogosExpr.h"

class LogosIf final : public LogosStmt {
public:
    LogosExpr* ifCond;
    LogosStmtBlock* ifStmtBlock;
    vector<LogosExpr*> elseIfConds;
    vector<LogosStmtBlock*> elseIfStmtBlocks;
    LogosStmtBlock* elseStmtBlock = nullptr;

    LogosIf(LogosExpr* ifCond, LogosStmtBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    void computeSimpleIf(CodeGenMetadata* metadata) const;
    void createElseBlock(CodeGenMetadata* metadata, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const;
    void computeComplexIf(CodeGenMetadata* metadata) const;
    ~LogosIf() override;
};



#endif //LOGOSIFSTMT_H
