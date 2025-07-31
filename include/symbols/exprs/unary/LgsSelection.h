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
    Value* resolveSelection(LgsCodeGen* codeGen);
    Value* hashValue(LgsCodeGen* codeGen) override;
    void createIRStmt(LgsCodeGen* codeGen) override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    ~LgsSelection() override;
};


