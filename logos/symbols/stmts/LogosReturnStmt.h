#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosReturnStmt final : public LogosStmt {
public:
    LogosExpr *expr = nullptr;

    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    explicit LogosReturnStmt(LogosExpr* expr) : expr(expr) {}
    ~LogosReturnStmt() override;
};



#endif //LOGOSRETURNSTMT_H
