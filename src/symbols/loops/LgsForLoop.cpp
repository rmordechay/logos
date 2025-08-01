#include "loops/LgsForLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this);
    initIRLoop(codeGen);
    stmtBlock->createIRValue(codeGen);
    IRLoopPrologue(codeGen);
    codeGen->startBlock(IRExitBlock);
    codeGen->stack.exitScope();
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
