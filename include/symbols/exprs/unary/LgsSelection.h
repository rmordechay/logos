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
    uint32_t hashValue(CodegenMetadata* metadata) override;
    Value* eqIR(CodegenMetadata* metadata, LgsExpr* other) override;
    void createIRStmt(CodegenMetadata* metadata) override;
    Value* createIRValue(CodegenMetadata* metadata) override;
    LgsExpr* resolveSelection(CodegenMetadata* metadata) const;
    json asJSON() override;
    ~LgsSelection() override;
};

#endif //SELECTION_H
