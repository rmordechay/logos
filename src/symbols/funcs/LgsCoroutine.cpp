#include "funcs/LgsCoroutine.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"
#include "utils/LgsUtils.h"

LgsCoroutine::~LgsCoroutine() {
    freeExpr(funcCall);
    funcCall = nullptr;
    freeExpr(selection);
    selection = nullptr;
}
