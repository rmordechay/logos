#include "stmts/LgsDeferStmt.h"
#include "data/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

#include <exprs/LgsFuncCall.h>
#include <exprs/LgsSelection.h>
#include <llvm/IR/Module.h>

LgsDeferStmt::~LgsDeferStmt() {
    freeExpr(funcCall);
    freeExpr(selection);
    funcCall = nullptr;
    selection = nullptr;
}
