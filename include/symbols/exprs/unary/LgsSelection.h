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
    Value* hashValue(LgsModule* module) override;
    Value* eqIR(LgsModule* module, LgsExpr* other) override;
    void createIRStmt(LgsModule* module) override;
    Value* createIRValue(LgsModule* module) override;
    void resolveSelection(LgsModule* module) const;
    ~LgsSelection() override;
};


