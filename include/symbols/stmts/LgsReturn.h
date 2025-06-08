#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(LgsRuntime* runtime) override;
    ~LgsReturn() override;
};




