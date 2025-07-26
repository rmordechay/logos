#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsReturn::createIRStmt(LgsModule* module) {
    if (expr) {
        addReturnExpr(module);
    } else {
        addReturnExpr(module);
    }
}

void LgsReturn::addReturnExpr(LgsModule* module) const {
    const auto currentFunc = module->stack.currentFunc();
    if (expr) {
        // This is to make sure IRValue is computed at
        // this point and not in the cleanup block
        expr->getIRValue(module);
        expr->parentBlock = module->builder.GetInsertBlock();
    }
    module->builder.CreateBr(currentFunc->cleanupBlock);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
