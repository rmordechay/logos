#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsInstance.h"

void LgsReturn::createIRStmt(Module* module) {
    if (expr->type->asObject()) {
        builder.CreateRetVoid();
    } else {
        const auto exprIR = expr->getIRValue(module);
        builder.CreateRet(exprIR);
    }
}

LgsReturn::~LgsReturn() {
    delete expr;
}
