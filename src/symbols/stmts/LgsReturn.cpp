#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::createIRStmt(LgsCodeGen* codeGen) {
    const auto currentFunc = codeGen->stack.currentFunc();
    if (expr) {
        expr->getIRValue(codeGen);
        if (returnStruct) {
            setReturnFlag(codeGen, true);
        }
        parentBlock = codeGen->builder.GetInsertBlock();
    }
    codeGen->builder.CreateBr(currentFunc->cleanupBlock);
}

Value* LgsReturn::getReturnFlag(LgsCodeGen* codeGen) const {
    const auto gep = codeGen->builder.CreateStructGEP(returnStruct->getAllocatedType(), returnStruct, 0);
    return codeGen->builder.CreateLoad(codeGen->i1Ty(), gep);
}

void LgsReturn::setReturnFlag(LgsCodeGen* codeGen, const bool returnFlag) const {
    const auto gep = codeGen->builder.CreateStructGEP(returnStruct->getAllocatedType(), returnStruct, 0);
    codeGen->builder.CreateStore(codeGen->i1(returnFlag), gep);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
