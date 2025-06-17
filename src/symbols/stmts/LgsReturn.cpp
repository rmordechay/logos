#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsRuntime* runtime) {
    if (hasTerminator(runtime)) return;
    const auto currentFunc = runtime->stack.currentFunc;
    if (expr) {
        const auto exprIR = expr->getIRValue(runtime);
        if (!currentFunc->funcType->isSwapReturn) {
            runtime->builder.CreateRet(exprIR);
        } else {
            runtime->builder.CreateRetVoid();
        }
    } else {
        runtime->builder.CreateRetVoid();
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
