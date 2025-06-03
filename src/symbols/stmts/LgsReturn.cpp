#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsInstance.h"


void LgsReturn::createIRStmt(LgsRuntime* runtime) {
    runtime->freeExprs(runtime);
    const auto exprIR = expr->getIRValue(runtime);
    builder.CreateRet(exprIR);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
