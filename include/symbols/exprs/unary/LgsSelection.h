#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include <stmts/LgsStmt.h>

class LgsUnaryExpr;

class LgsSelection final : public LgsStmt, public LgsUnaryExpr {
public:
    std::vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    string prettyName() override;
    LgsExpr* lastExpr() const;
    uint32_t hashValue(LgsRuntime* runtime) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    void createIRStmt(LgsRuntime* runtime) override;
    Value* createIRValue(LgsRuntime* runtime) override;
    LgsExpr* resolveSelection(LgsRuntime* runtime) const;
    json asJSON() override;
    ~LgsSelection() override;
};


