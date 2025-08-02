#include "stmts/LgsContinue.h"
#include <loops/LgsForLoop.h>

void LgsContinue::createIRStmt(LgsCodeGen* codeGen) {
    const auto currentLoop = codeGen->stack.currentLoop();
    currentLoop->incIndex(codeGen);
}
