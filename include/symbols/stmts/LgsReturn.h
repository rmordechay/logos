#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    json asJson() override;
    ~LgsReturn() override;
};



#endif //LOGOSRETURNSTMT_H
