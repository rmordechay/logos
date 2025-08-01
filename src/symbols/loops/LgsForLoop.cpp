#include "loops/LgsForLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    initIRLoop(codeGen);
    stmtsBlock->createIRValue(codeGen);
    IRLoopPrologue(codeGen);
    codeGen->startBlock(IRExitBlock);
    codeGen->stack.exitScope();
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
