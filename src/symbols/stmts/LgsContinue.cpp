#include "stmts/LgsContinue.h"
#include "logos/LgsCodeGen.h"
#include <loops/LgsForLoop.h>

void LgsContinue::createIRValue(LgsCodeGen* codeGen) {
    const auto currentLoop = codeGen->stack.currentLoop();
    currentLoop->incAndJumpToCond(codeGen);
}
