#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsModule* module) {
    if (lastInstTerminator(module)) assert(0);
    const auto currentFunc = module->stack.currentFunc;
    if (!expr || currentFunc->funcType->isSwapReturn) {
        module->builder.CreateRetVoid();
        return;
    }
    auto exprIR = expr->getIRValue(module);
    if (exprIR->getType()->isPointerTy()) {
        exprIR = module->builder.CreateLoad(expr->type->getIRType(module), exprIR);
    }
    module->builder.CreateRet(exprIR);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
