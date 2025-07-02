#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsModule* module) {
    if (hasTerminator(module)) return;
    const auto currentFunc = module->stack.currentFunc;
    if (expr) {
        const auto exprIR = expr->getIRValue(module);
        if (!currentFunc->funcType->isSwapReturn) {
            module->builder.CreateRet(exprIR);
        } else {
            module->builder.CreateRetVoid();
        }
    } else {
        module->builder.CreateRetVoid();
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
