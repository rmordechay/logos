#include "stmts/LgsBreakStmt.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsBreakStmt::createIRStmt(LgsRuntime* runtime) {
    const auto loop = runtime->stack.getLoop();
    const auto loopExit = loop->IRExitBlock;
    runtime->builder.CreateBr(loopExit);
    const auto breakBlock = BasicBlock::Create(context, "break");
    startBlock(runtime, breakBlock);
}
