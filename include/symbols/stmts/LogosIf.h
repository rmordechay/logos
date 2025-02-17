#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LogosStmt.h"
#include "LogosStmtBlock.h"
#include "exprs/LogosExpr.h"

class LogosIf final : public LogosStmt {
public:
    LogosExpr *cond = nullptr;
    LogosStmtBlock* stmtBlock = nullptr;

    explicit LogosIf(LogosExpr* cond, LogosStmtBlock* stmtBlock) : cond(cond), stmtBlock(stmtBlock) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosIf() override;
};



#endif //LOGOSIFSTMT_H
