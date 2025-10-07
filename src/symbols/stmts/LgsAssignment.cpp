#include "stmts/LgsAssignment.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsVariable.h"
#include "types/iterables/LgsVec.h"

std::string LgsAssignment::getAssignTypeStr() const {
    switch (assignmentType) {
    case ASSIGN:
        return "re";
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
    }
    assert(0);
}

LgsAssignment::~LgsAssignment() {
    delete lValue;
    delete rValue;
}
