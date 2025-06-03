#include "stmts/LgsBreakStmt.h"
#include "funcs/LgsFunc.h"

#include "loops/LgsForLoop.h"

void LgsBreakStmt::createIRStmt(Module* module, LgsRuntime* runtime) {
    const auto currentLoop = runtime->stack.currentLoop;
    const auto currentFunc = runtime->stack.currentFunc;
    const auto loopExit = currentLoop->loopExitBlock;
    builder.CreateBr(loopExit);
    const auto IRFunc = currentFunc->getIRFunc(module);
    const auto breakExtBlock = createBasicBlock("break_ext");
    breakExtBlock->insertInto(IRFunc);
    builder.SetInsertPoint(breakExtBlock);
}
