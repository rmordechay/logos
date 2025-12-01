#include "stmts/LgsDeferStmt.h"

#include <exprs/LgsFuncCall.h>
#include <exprs/LgsSelection.h>

void LgsDeferStmt::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsDeferStmt::~LgsDeferStmt() {
    freeExpr(funcCall);
    freeExpr(selection);
    funcCall = nullptr;
    selection = nullptr;
}
