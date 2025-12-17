#pragma once
#include "LgsBinaryTokens.h"
#include "LgsStmt.h"

class LgsArrayExpr;
class LgsHashMap;
struct LgsIndex;
class LgsIterIndex;
class LgsType;


class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue = nullptr;
    LgsExpr* rValue = nullptr;
    LgsAssignOp assignmentType;

    LgsAssignment(const LgsAssignOp& assignmentType, LgsExpr* lValue, LgsExpr* rValue) : lValue(lValue), rValue(rValue), assignmentType(assignmentType) {}
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsAssignment() override;
};
