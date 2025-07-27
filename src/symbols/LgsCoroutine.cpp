#include "LgsCoroutine.h"

#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"

void LgsCoroutine::createIRStmt(LgsModule* module) {
    if (stmtsBlock) {
        stmtsBlock->createIRValue(module);
    } else if (funcCall) {
        funcCall->getIRValue(module);
    } else if (selection) {
        selection->getIRValue(module);
    } else {
        assert(0);
    }
}
