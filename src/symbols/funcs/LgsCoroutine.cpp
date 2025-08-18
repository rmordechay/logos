#include "funcs/LgsCoroutine.h"
#include "builtins/LgsBuiltins.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"

json::object LgsCoroutine::asJSON() {
    json::object obj;
    return obj;
}

void LgsCoroutine::createIRValue(LgsCodeGen* codeGen) {
    const auto fc = funcCall ? funcCall : selection->lastExpr()->asFuncCall();
    const auto ctxTy = codeGen->getThunkCtxType(fc);
    const auto ctx = codeGen->getThunkCtxValue(fc, ctxTy);
    const auto func = codeGen->getThunkFunc(fc, ctxTy);
    codeGen->addCoro(func, ctx);
}

LgsCoroutine::~LgsCoroutine() {
    if (funcCall) {
        delete funcCall;
        funcCall = nullptr;
    }
    if (selection) {
        delete selection;
        selection = nullptr;
    }
}
