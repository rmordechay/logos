#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosReturnStmt final : public LogosStmt {
public:

    LogosExpr *expr;

    Value* getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) override;
    explicit LogosReturnStmt(LogosExpr* expr) : expr(expr) {}
    ~LogosReturnStmt() override = default;
};



#endif //LOGOSRETURNSTMT_H
