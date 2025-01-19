#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LogosStack.h"
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosIfStmt final : public LogosStmt {
public:
    LogosExpr *cond;
    vector<LogosStmt*> stmt;

    explicit LogosIfStmt(LogosExpr* cond, const vector<LogosStmt*>& stmt) : cond(cond), stmt(stmt) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosIfStmt() override = default;
};



#endif //LOGOSIFSTMT_H
