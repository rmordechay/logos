#pragma once
#include "LgsStmt.h"

class LgsArrayExpr;
class LgsHashMap;
struct LgsIndex;
class LgsIterIndex;
class LgsType;

enum LgsAssignType {
    ASSIGN,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_MUL,
    ASSIGN_DIV,
    ASSIGN_MOD,
    ASSIGN_POW,
    ASSIGN_AND,
    ASSIGN_OR,
    ASSIGN_XOR,
    ASSIGN_LSHIFT,
    ASSIGN_RSHIFT,
    ASSIGN_UNKNOWN,
};

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue = nullptr;
    LgsExpr* rValue = nullptr;
    LgsAssignType assignmentType;

    LgsAssignment(const LgsAssignType assignmentType, LgsExpr* lValue, LgsExpr* rValue) : lValue(lValue), rValue(rValue), assignmentType(assignmentType) {}
    std::string getAssignTypeStr() const;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsAssignment() override;
};
