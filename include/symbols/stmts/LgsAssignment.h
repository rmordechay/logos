#pragma once
#include "LgsStmt.h"
#include "exprs/unary/LgsSelection.h"

class LgsExpr;
class LgsType;

enum AssignmentType {
    ASSIGN,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_MUL,
    ASSIGN_DIV,
};

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue;
    LgsExpr* rValue;

    void createIRStmt(LgsRuntime* runtime) override;
    void assignToIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void assignToSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* value) const;
    void assignToVariable(LgsRuntime* runtime, LgsVariable* var, LgsExpr* value) const;
    void storeScalarInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void storeArrayInIterIndex(LgsRuntime* runtime, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) const;
    void storeHashMapInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsHashMap* map) const;
    ~LgsAssignment() override;
};


