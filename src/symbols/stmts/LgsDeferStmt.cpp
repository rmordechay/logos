#include "stmts/LgsDeferStmt.h"
#include "data/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

#include <exprs/LgsFuncCall.h>
#include <exprs/LgsSelection.h>
#include <llvm/IR/Module.h>

json::value LgsDeferStmt::asJsonStr() {
    json::object obj;
    obj["stmtKind"] = "DeferStmt";
    obj["funcCall"] = funcCall ? funcCall->asJsonStr() : nullptr;
    obj["selection"] = selection ? selection->asJsonStr() : nullptr;
    return obj;
}

LgsDeferStmt::~LgsDeferStmt() {
    freeExpr(funcCall);
    freeExpr(selection);
    funcCall = nullptr;
    selection = nullptr;
}
