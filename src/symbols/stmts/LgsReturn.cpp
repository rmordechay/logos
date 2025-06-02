#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsInstance.h"
#include "logos/LgsGlobals.h"

void LgsReturn::createIRStmt(Module* module) {
    runtime.freeExprs(module);
    const auto exprIR = expr->getIRValue(module);
    builder.CreateRet(exprIR);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
