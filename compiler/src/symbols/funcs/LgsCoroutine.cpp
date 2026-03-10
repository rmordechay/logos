#include "funcs/LgsCoroutine.h"

#include <assert.h>

#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsExpr.h"

void LgsCoroutine::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsCoroutine::~LgsCoroutine() {
    freeExpr(funcCall);
    funcCall = nullptr;
    freeExpr(selection);
    selection = nullptr;
}
