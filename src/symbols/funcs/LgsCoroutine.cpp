#include "funcs/LgsCoroutine.h"
#include "builtins/LgsPrint.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"

json::value LgsCoroutine::asJSON() {
    assert(0);
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
