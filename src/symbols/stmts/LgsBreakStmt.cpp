#include "stmts/LgsBreakStmt.h"
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "types/LgsFuncType.h"

void LgsBreakStmt::createIRStmt(CodegenMetadata* metadata) {
    const auto currentLoop = metadata->runtime.getCurrentLoop();
    const auto currentFunc = metadata->runtime.getCurrentFunc();
    const auto loopExit = currentLoop->loopExitBlock;
    metadata->builder.CreateBr(loopExit);
    const auto IRFunc = currentFunc->getIRFunc(metadata);
    const auto breakExtBlock = createBasicBlock("break_ext");
    breakExtBlock->insertInto(IRFunc);
    metadata->builder.SetInsertPoint(breakExtBlock);
}
