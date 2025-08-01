#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    const auto withCleanup = codeGen->stack.currentStmtsBlock()->needsCleanup();
    if (expr) {
        const auto exprIR = expr->getIRValue(codeGen);
        if (withCleanup) {
            codeGen->branchToCleanup(exprIR);
        } else {
            codeGen->callPopStack();
            codeGen->builder.CreateRet(exprIR);
        }
    } else {
        if (withCleanup) {
            codeGen->branchToCleanup();
        } else {
            codeGen->callPopStack();
            codeGen->builder.CreateRetVoid();
        }
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
