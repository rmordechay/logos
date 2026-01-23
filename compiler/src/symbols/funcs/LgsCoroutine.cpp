#include "funcs/LgsCoroutine.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"

void LgsCoroutine::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsCoroutine::~LgsCoroutine() {
    freeExpr(funcCall);
    funcCall = nullptr;
    freeExpr(selection);
    selection = nullptr;
}
