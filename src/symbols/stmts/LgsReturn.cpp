#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsInstance.h"

void LgsReturn::createIRStmt(LgsRuntime* runtime) {
    const auto currentFunc = runtime->stack.currentFunc;
    if (expr) {
        const auto exprIR = expr->getIRValue(runtime);
        runtime->freeExprs();
        if (!currentFunc->funcType->hasFlag(SWAP_RETURN)) {
            runtime->builder.CreateRet(exprIR);
        } else {
            runtime->builder.CreateRetVoid();
        }
    } else {
        runtime->freeExprs();
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
