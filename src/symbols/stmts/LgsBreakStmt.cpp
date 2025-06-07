#include "stmts/LgsBreakStmt.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsRuntime.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsBreakStmt::createIRStmt(LgsRuntime* runtime) {
    BasicBlock* loopExit = nullptr;
    if (breakIfStmt) {
        const auto ifStmt = runtime->stack.getIfStmt();
        loopExit = ifStmt->IRIfEndBlock;
    } else {
        const auto loop = runtime->stack.getLoop();
        loopExit = loop->loopExitBlock;
    }
    runtime->builder.CreateBr(loopExit);
    breakBlock = createBasicBlock("break", context);
    startBlock(runtime, breakBlock);
    runtime->builder.SetInsertPoint(breakBlock);
}
