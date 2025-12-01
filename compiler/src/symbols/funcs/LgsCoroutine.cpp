#include "funcs/LgsCoroutine.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"

void LgsCoroutine::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsCoroutine::~LgsCoroutine() {
    freeExpr(funcCall);
    funcCall = nullptr;
    freeExpr(selection);
    selection = nullptr;
}
