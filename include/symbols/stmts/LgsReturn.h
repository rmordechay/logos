#ifndef LOGOSRETURNSTMT_H
#define LOGOSRETURNSTMT_H
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(CodeGenMetadata* metadata) override;
    ~LgsReturn() override;
};



#endif //LOGOSRETURNSTMT_H
