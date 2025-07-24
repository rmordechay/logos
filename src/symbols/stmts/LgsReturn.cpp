#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsModule* module) {
    const auto currentFunc = module->stack.currentFunc;
    if (!expr || currentFunc->funcType->isSwapReturn) {
        currentFunc->branchToCleanup(module);
        return;
    }
    auto exprIR = expr->getIRValue(module);
    if (exprIR->getType()->isPointerTy()) {
        exprIR = module->builder.CreateLoad(expr->type->getIRType(module), exprIR);
    }
    module->stack.currentFunc->returnValue = exprIR;
    currentFunc->branchToCleanup(module);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
