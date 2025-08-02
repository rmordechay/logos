#include "stmts/LgsBreak.h"
#include "loops/LgsForLoop.h"

void LgsBreak::createIRStmt(LgsCodeGen* codeGen) {
    const auto loop = codeGen->stack.currentLoop();
    codeGen->builder.CreateBr(loop->IRExitBlock);
}
