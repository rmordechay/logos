#include "stmts/LgsContinue.h"
#include "logos/LgsCodeGen.h"
#include <loops/LgsForLoop.h>

json::value_ref LgsContinue::asJSON() {
    json::object obj;
    return obj;
}

void LgsContinue::createIRValue(LgsCodeGen* codeGen) {
    const auto currentLoop = codeGen->stack.currentLoop();
    currentLoop->incAndJumpToCond(codeGen);
}
