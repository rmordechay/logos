#include "stmts/LgsContinue.h"
#include "logos/LgsCodeGen.h"
#include <loops/LgsForLoop.h>

json::value LgsContinue::asJSON() {
    assert(0);
}

void LgsContinue::createIRValue(LgsCodeGen* codeGen) {
    const auto currentLoop = codeGen->stack.currentLoop();
    currentLoop->incAndJumpToCond(codeGen);
}
