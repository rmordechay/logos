#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsModule* module) {
    const auto currentFunc = module->stack.currentFunc();
    if (!expr || currentFunc->funcType->isSwapReturn) {
        currentFunc->addReturnExpr(module, nullptr);
        return;
    }
    auto exprIR = expr->getIRValue(module);
    if (exprIR->getType()->isPointerTy()) {
        const auto ty = expr->type->getIRType(module);
        exprIR = module->builder.CreateLoad(ty, exprIR);
    }
    currentFunc->addReturnExpr(module, exprIR);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
