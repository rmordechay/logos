#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LogosStmt.h"
#include "LogosStmtBlock.h"
#include "exprs/LogosExpr.h"

class LogosIf final : public LogosStmt {
public:
    LogosExpr* ifCond;
    LogosStmtBlock* ifStmtBlock;
    vector<LogosExpr*> ifElseConds;
    vector<LogosStmtBlock*> ifElseStmtBlocks;
    LogosStmtBlock* elseStmtBlock = nullptr;

    LogosIf(LogosExpr* ifCond, LogosStmtBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosIf() override;
};



#endif //LOGOSIFSTMT_H
