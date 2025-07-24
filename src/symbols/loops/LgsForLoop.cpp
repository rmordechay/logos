#include "loops/LgsForLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsModule* module) {
    module->stack.enterScope(LOOP_SCOPE, this);
    initIRLoop(module);
    stmtBlock->createIRValue(module);
    exitIRLoop(module);
    module->stack.exitScope();
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
