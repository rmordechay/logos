#include "stmts/LgsBreakStmt.h"
#include "loops/LgsForLoop.h"

void LgsBreakStmt::createIRStmt(LgsModule* module) {
    const auto loop = module->stack.currentLoop();
    const auto loopExit = loop->IRExitBlock;
    module->builder.CreateBr(loopExit);
}
