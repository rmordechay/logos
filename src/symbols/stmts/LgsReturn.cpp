#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsStmtsBlock.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRValue(LgsCodeGen* codeGen) {
    const auto exprIR = expr ? expr->getIRValue(codeGen) : nullptr;
    const auto currentFunc = codeGen->stack.currentFunc();
    const auto currentStmtsBlock = codeGen->stack.currentStmtsBlock();
    const auto withCleanup = currentStmtsBlock->needsCleanup();
    if (withCleanup) {
        const auto cleanupBlock = currentStmtsBlock->getCleanupBlock(codeGen);
        if (codeGen->stack.isRootScope()) {
            parentBlock = codeGen->builder.GetInsertBlock();
        } else {
            parentBlock = cleanupBlock;
        }
        codeGen->builder.CreateBr(cleanupBlock);
    } else {
        if (currentFunc->funcType->rt->isVoid()) {
            codeGen->builder.CreateRetVoid();
        } else {
            codeGen->builder.CreateRet(exprIR);
        }
    }
}

json::value LgsReturn::asJSON() {
    assert(0);
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
