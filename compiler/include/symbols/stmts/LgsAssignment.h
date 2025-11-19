#pragma once
#include "LgsStmt.h"
#include "LgsTokens.h"
#include "exprs/LgsExpr.h"

class LgsArrayExpr;
class LgsHashMap;
struct LgsIndex;
class LgsIterIndex;
class LgsType;

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue = nullptr;
    LgsExpr* rValue = nullptr;
    LgsAssignType assignmentType;

    LgsAssignment(const LgsAssignType assignmentType, LgsExpr* lValue, LgsExpr* rValue) : lValue(lValue), rValue(rValue), assignmentType(assignmentType) {}
    std::string getAssignTypeStr() const;
    ~LgsAssignment() override;
};
