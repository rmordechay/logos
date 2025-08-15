#include "stmts/LgsDeferStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsSelection.h>
#include <llvm/IR/Module.h>

void LgsDeferStmt::createIRValue(LgsCodeGen* codeGen) {
    const auto fc = funcCall ? funcCall : selection->lastExpr()->asFuncCall();
    const auto ctxTy = codeGen->getThunkCtxType(fc);
    const auto ctx = codeGen->getThunkCtxValue(fc, ctxTy);
    const auto func = codeGen->getThunkFunc(fc, ctxTy);
    codeGen->addDeferFunc(func, ctx);
}

void LgsDeferStmt::generateIR(LgsCodeGen* codeGen) const {
    if (funcCall) {
        funcCall->createIRValue(codeGen);
    } else if (selection) {
        selection->createIRValue(codeGen);
    }
}

LgsDeferStmt::~LgsDeferStmt() {
    if (funcCall) {
        delete funcCall;
        funcCall = nullptr;
    }
    if (selection) {
        delete selection;
        selection = nullptr;
    }
}
