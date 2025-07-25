#pragma once
#include "LgsStmt.h"

class LgsArrayExpr;
class LgsHashMap;
struct LgsIndex;
class LgsIterIndex;
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
    void createIRStmt(LgsModule* module) override;
    void createIRAssign(LgsModule* module) const;
    void assignToIterIndex(LgsModule* module, LgsIterIndex* iterIndex, LgsExpr* expr) const;
    void storeArrayInIterIndex(LgsModule* module, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr) const;
    void setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices) const;
    static void assignToSelection(LgsModule* module, const LgsSelection* selection, LgsExpr* expr);
    static void assignToVariable(LgsModule* module, LgsVariable* variable, LgsExpr* expr);
    static void storeScalarInIterIndex(LgsModule* module, LgsIterIndex* iterIndex, LgsExpr* expr);
    static void storeHashMapInIterIndex(LgsModule* module, LgsIterIndex* iterIndex, LgsHashMap* map);
    ~LgsAssignment() override;
};
