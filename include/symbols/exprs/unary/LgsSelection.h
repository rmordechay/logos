#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include <stmts/LgsStmt.h>

class LgsUnaryExpr;

enum LgsSelectionType {
    SELECTION_FUNC_CALL,
    SELECTION_FIELD,
    SELECTION_ITER_INDEX,
    SELECTION_UNKNOWN,
};

class LgsSelection final : public LgsStmt, public LgsUnaryExpr {
public:
    LgsSelectionType selectionType = SELECTION_UNKNOWN;
    std::vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    string prettyName() override;
    LgsExpr* lastExpr() const;
    LgsExpr* LastExprParent() const;
    Value* resolveSelection(LgsModule* module);
    Value* hashValue(LgsModule* module) override;
    void createIRStmt(LgsModule* module) override;
    Value* createIRValue(LgsModule* module) override;
    ~LgsSelection() override;
};


