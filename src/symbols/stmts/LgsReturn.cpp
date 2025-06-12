#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsRuntime* runtime) {
    const auto currentFunc = runtime->stack.currentFunc;
    if (expr) {
        const auto exprIR = expr->getIRValue(runtime);
        runtime->freeExprs();
        if (!currentFunc->funcType->isSwapReturn) {
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
