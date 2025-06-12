#pragma once
#include "LgsStmt.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"

#include <vector>

class LgsExpr;
class LgsType;

enum LgsAssignType {
    ASSIGN,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_MUL,
    ASSIGN_DIV,
    ASSIGN_MOD,
    ASSIGN_AND,
    ASSIGN_OR,
    ASSIGN_XOR,
    ASSIGN_LSHIFT,
    ASSIGN_RSHIFT,
};

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue = nullptr;
    LgsExpr* rValue = nullptr;
    LgsAssignType assignmentType;

    LgsAssignment(const LgsAssignType assignmentType, LgsExpr* lValue, LgsExpr* rValue) : lValue(lValue), rValue(rValue), assignmentType(assignmentType) {}
    void createIRStmt(LgsRuntime* runtime) override;
    void createIRAssign(LgsRuntime* runtime) const;
    void assignToIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void assignToSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* value) const;
    void assignToVariable(LgsRuntime* runtime, LgsVariable* var, LgsExpr* value) const;
    void storeScalarInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void storeArrayInIterIndex(LgsRuntime* runtime, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) const;
    void setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices) const;
    void storeHashMapInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsHashMap* map) const;
    ~LgsAssignment() override;
};


