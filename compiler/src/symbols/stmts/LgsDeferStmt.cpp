#include "stmts/LgsDeferStmt.h"
#include "LgsUtils.h"

#include <exprs/LgsFuncCall.h>
#include <exprs/LgsSelection.h>

LgsDeferStmt::~LgsDeferStmt() {
    freeExpr(funcCall);
    freeExpr(selection);
    funcCall = nullptr;
    selection = nullptr;
}
