#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "types/LgsVec.h"

json::value LgsAssignment::asJSON() {
    json::object obj;
    obj["lValue"] = lValue->asJSON();
    obj["rValue"] = rValue->asJSON();
    obj["assignmentType"] = assignmentType;
    return obj;
}

LgsAssignment::~LgsAssignment() {
    delete lValue;
    delete rValue;
}
