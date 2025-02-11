#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosReturnStmt final : public LogosStmt {
public:
    LogosExpr *expr = nullptr;

    explicit LogosReturnStmt(LogosExpr* expr) : expr(expr) {}
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosReturnStmt() override;
};



#endif //LOGOSRETURNSTMT_H
