#include "stmts/LgsContinueStmt.h"

#include "funcs/LgsFunc.h"

#include <loops/LgsForLoop.h>

void LgsContinueStmt::createIRStmt(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto currentLoop = metadata->runtime.getCurrentLoop();
    const auto loopCondition = currentLoop->loopCondBlock;
    const auto iValue = builder.CreateLoad(i32Ty, currentLoop->iPtr);
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, currentLoop->iPtr);
    builder.CreateBr(loopCondition);
}
