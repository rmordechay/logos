#ifndef SELECTION_H
#define SELECTION_H
#include "exprs/unary/LgsUnaryExpr.h"
#include <stmts/LgsStmt.h>

class LgsUnaryExpr;

class LgsSelection final : public LgsStmt, public LgsUnaryExpr {
public:
    vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    string getName() override;
    LgsExpr* lastExpr() const;
    uint32_t hashValue(Module* module) override;
    Value* eqIR(Module* module, LgsExpr* other) override;
    void createIRStmt(Module* module) override;
    Value* createIRValue(Module* module) override;
    LgsExpr* resolveSelection(Module* module) const;
    json asJSON() override;
    ~LgsSelection() override;
};

#endif //SELECTION_H
