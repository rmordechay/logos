#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    const auto withCleanup = codeGen->stack.getCurrentStmtsBlock()->needsCleanup();
    if (withCleanup) {
        const auto exprIR = expr ? expr->getIRValue(codeGen) : nullptr;
        codeGen->branchToCleanup(exprIR);
    } else {
        if (expr) {
            const auto exprIR = expr->getIRValue(codeGen);
            if (!codeGen->stack.getCurrentFunc()->funcType->rt->isVoid) {
                codeGen->callPopStack();
                codeGen->builder.CreateRet(exprIR);
                return;
            }
        }
        codeGen->callPopStack();
        codeGen->builder.CreateRetVoid();
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
