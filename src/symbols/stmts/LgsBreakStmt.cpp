#include "stmts/LgsBreakStmt.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsBreakStmt::createIRStmt(LgsModule* module) {
    const auto loop = module->stack.getLoop();
    const auto loopExit = loop->IRExitBlock;
    module->builder.CreateBr(loopExit);
    const auto breakBlock = BasicBlock::Create(module->context, "break");
}
