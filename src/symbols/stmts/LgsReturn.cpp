#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsInstance.h"

void LgsReturn::createIRStmt(LgsRuntime* runtime) {
    runtime->freeExprs();
    const auto currentFunc = runtime->stack.currentFunc;
    if (expr) {
        const auto exprIR = expr->getIRValue(runtime);
        if (!currentFunc->funcType.swapReturn) {
            runtime->builder.CreateRet(exprIR);
        }
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
