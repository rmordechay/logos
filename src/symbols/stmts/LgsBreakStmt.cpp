#include "stmts/LgsBreakStmt.h"
#include "loops/LgsForLoop.h"

void LgsBreakStmt::createIRStmt(LgsCodeGen* codeGen) {
    const auto loop = codeGen->stack.currentLoop();
    codeGen->builder.CreateBr(loop->IRExitBlock);
}
