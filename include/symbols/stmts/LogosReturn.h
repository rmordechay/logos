#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosReturn final : public LogosStmt {
public:
    LogosExpr *expr = nullptr;

    explicit LogosReturn(LogosExpr* expr) : expr(expr) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosReturn() override;
};



#endif //LOGOSRETURNSTMT_H
