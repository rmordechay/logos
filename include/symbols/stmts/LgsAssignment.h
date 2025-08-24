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
    void createIRAssignment(LgsLLVM& codeGen) const;
    static void assignToIterIndex(LgsIterIndex* iterIndex, LgsExpr* expr, LgsLLVM* codeGen);
    static void assignArrayToIterIndex(LgsLLVM* codeGen, const LgsIterIndex* iterIndex, const LgsArrayExpr* arr);
    static void assignToSelection(LgsLLVM* codeGen, LgsSelection* selection, LgsExpr* expr);
    static void assignToVariable(LgsLLVM* codeGen, LgsVariable* variable, LgsExpr* expr);
    static void assignScalarToIterIndex(LgsLLVM& codeGen, LgsIterIndex* iterIndex, LgsExpr* expr);
    static void assignHashMapToIterIndex(LgsLLVM* codeGen, LgsIterIndex* iterIndex, LgsHashMap* map);
    json::value asJSON() override;
    ~LgsAssignment() override;
};
