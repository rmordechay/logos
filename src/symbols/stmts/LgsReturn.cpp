#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    const auto exprIR = expr ? expr->getIRValue(codeGen) : nullptr;
    const auto currentFunc = codeGen->stack.currentFunc();
    const auto currentStmtsBlock = codeGen->stack.currentStmtsBlock();
    const auto withCleanup = currentStmtsBlock->needsCleanup();
    if (withCleanup) {
        if (exprIR) {
            currentFunc->returnPhiNode->addIncoming(exprIR, codeGen->builder.GetInsertBlock());
        }
        const auto cleanupBlock = currentStmtsBlock->getCleanupBlock(codeGen);
        codeGen->builder.CreateBr(cleanupBlock);
    } else {
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
