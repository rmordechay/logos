#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosIf final : public LogosStmt {
public:
    LogosExpr *cond;
    vector<LogosStmt*> stmts;

    explicit LogosIf(LogosExpr* cond, const vector<LogosStmt*>& stmt) : cond(cond), stmts(stmt) {}
    Value* writeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosIf() override;
};



#endif //LOGOSIFSTMT_H
