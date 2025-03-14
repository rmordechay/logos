#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LgsStmt.h"
#include "LogosExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LogosExpr *expr = nullptr;

    explicit LgsReturn(LogosExpr* expr) : expr(expr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsReturn() override;
};



#endif //LOGOSRETURNSTMT_H
