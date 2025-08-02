#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    parentBlock = codeGen->builder.GetInsertBlock();
    const auto exprIR = expr ? expr->getIRValue(codeGen) : nullptr;
    const auto currentStmtsBlock = codeGen->stack.currentStmtsBlock();
    const auto withCleanup = currentStmtsBlock->needsCleanup();
    if (withCleanup) {
        const auto cleanupBlock = currentStmtsBlock->getCleanupBlock(codeGen);
        codeGen->builder.CreateBr(cleanupBlock);
    } else {
        const auto currentFunc = codeGen->stack.currentFunc();
        if (currentFunc->funcType->rt->isVoid) {
            codeGen->builder.CreateRetVoid();
        } else {
            codeGen->builder.CreateRet(exprIR);
        }
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
