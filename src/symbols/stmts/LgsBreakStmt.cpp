#include "stmts/LgsBreakStmt.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsGlobals.h"
#include "loops/LgsForLoop.h"

void LgsBreakStmt::createIRStmt(Module* module) {
    const auto currentLoop = runtime.getCurrentLoop();
    const auto currentFunc = runtime.getCurrentFunc();
    const auto loopExit = currentLoop->loopExitBlock;
    builder.CreateBr(loopExit);
    const auto IRFunc = currentFunc->getIRFunc(module);
    const auto breakExtBlock = createBasicBlock("break_ext");
    breakExtBlock->insertInto(IRFunc);
    builder.SetInsertPoint(breakExtBlock);
}
