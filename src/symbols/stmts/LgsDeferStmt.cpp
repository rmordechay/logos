#include "stmts/LgsDeferStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsSelection.h>
#include <llvm/IR/Module.h>

void LgsDeferStmt::createIRValue(LgsCodeGen* codeGen) {
    const auto fc = funcCall ? funcCall : selection->lastExpr()->asFuncCall();
    const auto ctxTy = codeGen->getThunkCtxType(fc);
    const auto ctx = codeGen->getThunkCtx(fc, ctxTy);
    const auto func = codeGen->getThunkFunc(fc, ctxTy);
    codeGen->addDeferFunc(func, ctx);
}

json::value LgsDeferStmt::asJSON() {
    assert(0);
}

LgsDeferStmt::~LgsDeferStmt() {
    freeExpr(funcCall);
    freeExpr(selection);
    funcCall = nullptr;
    selection = nullptr;
}
