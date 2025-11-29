#include "funcs/LgsCoroutine.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"

LgsCoroutine::~LgsCoroutine() {
    freeExpr(funcCall);
    funcCall = nullptr;
    freeExpr(selection);
    selection = nullptr;
}
