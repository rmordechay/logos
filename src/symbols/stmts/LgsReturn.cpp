#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    const auto currentFunc = codeGen->stack.currentFunc();
    if (expr) {
        expr->getIRValue(codeGen);
        parentBlock = codeGen->builder.GetInsertBlock();
    }
    codeGen->builder.CreateBr(currentFunc->cleanupBlock);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
