#include "stmts/LgsBreakStmt.h"

#include "funcs/LgsFunc.h"

#include <loops/LgsLoop.h>

Value* LgsBreakStmt::createIRValue(CodeGenMetadata* metadata) {
    const auto currentLoop = metadata->lgsStack.currentLoop;
    const auto currentFunc = metadata->lgsStack.currentFunc;
    const auto loopExit = currentLoop->loopExitBlock;
    const auto branch = metadata->builder.CreateBr(loopExit);
    const auto IRFunc = currentFunc->getIRFunc(metadata);
    const auto breakExtBlock = createBasicBlock("break_ext");
    breakExtBlock->insertInto(IRFunc);
    metadata->builder.SetInsertPoint(breakExtBlock);
    return branch;
}
