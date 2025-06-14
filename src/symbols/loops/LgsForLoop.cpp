#include "loops/LgsForLoop.h"
#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsRuntime* runtime) {
    runtime->stack.enterScope(LOOP_SCOPE, this);
    initIRLoop(runtime);
    stmtBlock->createIRValue(runtime);
    exitIRLoop(runtime);
    runtime->stack.exitScope(LOOP_SCOPE);
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
