#pragma once
#include "LgsStmt.h"
#include "exprs/unary/LgsSelection.h"

class LgsExpr;
class LgsType;

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue;
    LgsExpr* rValue;

    void createIRStmt(LgsRuntime* runtime) override;
    void assignToIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void assignToSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* expr) const;
    void storeScalarInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void storeArrayInIterIndex(LgsRuntime* runtime, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) const;
    void storeHashMapInIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsHashMap* map) const;
    ~LgsAssignment() override;
};


