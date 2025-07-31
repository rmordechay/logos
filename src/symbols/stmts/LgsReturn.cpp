#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    const auto currentFunc = codeGen->stack.currentFunc();
    if (expr) {
        const auto exprIR = expr->getIRValue(codeGen);
        parentBlock = codeGen->builder.GetInsertBlock();
        if (returnStructPtr) {
            setReturnFlag(codeGen, true);
            setReturnValue(codeGen, exprIR);
        }
        codeGen->builder.CreateBr(currentFunc->cleanupBlock);
    }
}

void LgsReturn::setReturnFlag(LgsCodeGen* codeGen, const bool value) const {
    const auto rsType = returnStructPtr->getResultElementType();
    const auto gep = codeGen->builder.CreateStructGEP(rsType, returnStructPtr, 0);
    codeGen->builder.CreateStore(codeGen->i1(value), gep);
}

void LgsReturn::setReturnValue(LgsCodeGen* codeGen, Value* value) const {
    const auto rsType = returnStructPtr->getResultElementType();
    const auto gep = codeGen->builder.CreateStructGEP(rsType, returnStructPtr, 1);
    codeGen->builder.CreateStore(value, gep);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
