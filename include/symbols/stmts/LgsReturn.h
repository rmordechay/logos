#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LgsStmt.h"
#include "LogosExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsReturn() override;
};



#endif //LOGOSRETURNSTMT_H
