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
    void createIRValue(LgsCodeGen* codeGen) override;
    void createIRAssignment(LgsCodeGen* codeGen) const;
    static void assignToIterIndex(LgsIterIndex* iterIndex, LgsExpr* expr, LgsCodeGen* codeGen);
    static void assignArrayToIterIndex(LgsCodeGen* codeGen, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr);
    static void assignToSelection(LgsCodeGen* codeGen, LgsSelection* selection, LgsExpr* expr);
    static void assignToVariable(LgsCodeGen* codeGen, LgsVariable* variable, LgsExpr* expr);
    static void assignScalarToIterIndex(LgsCodeGen* codeGen, LgsIterIndex* iterIndex, LgsExpr* expr);
    static void assignHashMapToIterIndex(LgsCodeGen* codeGen, LgsIterIndex* iterIndex, LgsHashMap* map);
    json::value asJSON() override;
    ~LgsAssignment() override;
};
