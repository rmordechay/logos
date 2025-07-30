#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    if (expr) {
        addReturnExpr(codeGen);
    } else {
        addReturnExpr(codeGen);
    }
}

void LgsReturn::addReturnExpr(LgsCodeGen* codeGen) const {
    const auto currentFunc = codeGen->stack.currentFunc();
    if (expr) {
        // This is to make sure IRValue is computed at
        // this point and not in the cleanup block
        expr->getIRValue(codeGen);
        expr->parentBlock = codeGen->builder.GetInsertBlock();
    }
    codeGen->builder.CreateBr(currentFunc->cleanupBlock);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
