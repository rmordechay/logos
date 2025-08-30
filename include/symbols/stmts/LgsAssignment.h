#pragma once
#include "LgsAssignable.h"
#include "LgsStmt.h"
#include "LgsType.h"

class LgsArrayExpr;
class LgsHashMap;
struct LgsIndex;
class LgsIterIndex;
class LgsExpr;
class LgsType;

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue = nullptr;
    LgsExpr* rValue = nullptr;
    LgsAssignType assignmentType;

    LgsAssignment(const LgsAssignType assignmentType, LgsExpr* lValue, LgsExpr* rValue) : lValue(lValue), rValue(rValue), assignmentType(assignmentType) {}
    json::value asJSON() override;
    std::string getAssignTypeStr() const;
    ~LgsAssignment() override;
};
