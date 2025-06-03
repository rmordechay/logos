#include "stmts/LgsBreakStmt.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsRuntime.h"

#include "loops/LgsForLoop.h"

void LgsBreakStmt::createIRStmt(LgsRuntime* runtime) {
    const auto currentLoop = runtime->stack.currentLoop;
    const auto currentFunc = runtime->stack.currentFunc;
    const auto loopExit = currentLoop->loopExitBlock;
    runtime->builder.CreateBr(loopExit);
    const auto IRFunc = currentFunc->getIRFunc(runtime);
    const auto breakExtBlock = createBasicBlock("break_ext", context);
    breakExtBlock->insertInto(IRFunc);
    runtime->builder.SetInsertPoint(breakExtBlock);
}
