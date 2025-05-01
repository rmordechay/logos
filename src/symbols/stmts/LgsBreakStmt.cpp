#include "stmts/LgsBreakStmt.h"

#include "funcs/LgsFunc.h"

#include <loops/LgsLoop.h>

void LgsBreakStmt::createIRStmt(CodeGenMetadata* metadata) {
    const auto currentLoop = metadata->lgsStack.currentLoop;
    const auto currentFunc = metadata->lgsStack.currentFunc;
    const auto loopExit = currentLoop->loopExitBlock;
    metadata->builder.CreateBr(loopExit);
    const auto IRFunc = currentFunc->getIRFunc(metadata);
    const auto breakExtBlock = createBasicBlock("break_ext");
    breakExtBlock->insertInto(IRFunc);
    metadata->builder.SetInsertPoint(breakExtBlock);
}
