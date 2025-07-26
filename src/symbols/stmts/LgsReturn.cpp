#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsModule* module) {
    const auto currentFunc = module->stack.currentFunc();
    if (expr) {
        currentFunc->addReturnExpr(module, expr);
    } else {
        currentFunc->addReturnExpr(module, nullptr);
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
