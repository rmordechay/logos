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
    Value* hashValue(LgsModule* runtime) override;
    Value* eqIR(LgsModule* runtime, LgsExpr* other) override;
    void createIRStmt(LgsModule* runtime) override;
    Value* createIRValue(LgsModule* runtime) override;
    void resolveSelection(LgsModule* runtime) const;
    ~LgsSelection() override;
};


