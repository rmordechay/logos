#include "stmts/LgsBreakStmt.h"
#include "loops/LgsForLoop.h"

void LgsBreakStmt::createIRStmt(LgsCodeGen* codeGen) {
    const auto loop = codeGen->stack.getCurrentLoop();
    codeGen->builder.CreateBr(loop->IRExitBlock);
}
