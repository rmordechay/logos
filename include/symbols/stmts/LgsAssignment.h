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
    void assignIRIterIndex(LgsRuntime* runtime, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void assignIRSelection(LgsRuntime* runtime, const LgsSelection* selection, LgsExpr* expr) const;
    ~LgsAssignment() override;
};


