#include "funcs/LgsCoroutine.h"
#include "builtins/LgsPrint.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"

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
