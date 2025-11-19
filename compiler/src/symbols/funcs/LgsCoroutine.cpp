#include "funcs/LgsCoroutine.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"
#include "LgsUtils.h"

LgsCoroutine::~LgsCoroutine() {
    freeExpr(funcCall);
    funcCall = nullptr;
    freeExpr(selection);
    selection = nullptr;
}
