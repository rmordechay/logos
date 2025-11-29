#include "stmts/LgsAssignment.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsVariable.h"
#include "LgsUtils.h"

std::string LgsAssignment::getAssignTypeStr() const {
    switch (assignmentType) {
    case ASSIGN:
        return "assign";
    case ASSIGN_ADD:
        return "add";
    case ASSIGN_SUB:
        return "subtract";
    case ASSIGN_MUL:
        return "multiply";
    case ASSIGN_DIV:
        return "divide";
    case ASSIGN_MOD:
        return "modulo";
    case ASSIGN_AND:
        return "and";
    case ASSIGN_OR:
        return "or";
    case ASSIGN_XOR:
        return "xor";
    case ASSIGN_LSHIFT:
        return "lshift";
    case ASSIGN_RSHIFT:
        return "rshift";
    case ASSIGN_POW:
        return "pow";
    case ASSIGN_UNKNOWN:
        break;
    }
    assert(0);
}

LgsAssignment::~LgsAssignment() {
    freeExpr(lValue);
    freeExpr(rValue);
    lValue = nullptr;
    rValue = nullptr;
}
