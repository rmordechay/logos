#include "stmts/LgsDeferStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsSelection.h>
#include <llvm/IR/Module.h>

json::value LgsDeferStmt::asJSON() {
    json::object obj;
    obj["stmtKind"] = "DeferStmt";
    obj["funcCall"] = funcCall ? funcCall->asJSON() : nullptr;
    obj["selection"] = selection ? selection->asJSON() : nullptr;
    return obj;
}

LgsDeferStmt::~LgsDeferStmt() {
    freeExpr(funcCall);
    freeExpr(selection);
    funcCall = nullptr;
    selection = nullptr;
}
