#include "stmts/LgsContinueStmt.h"

#include "funcs/LgsFunc.h"

#include <loops/LgsLoop.h>

void LgsContinueStmt::createIRStmt(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto currentLoop = metadata->lgsStack.currentLoop;
    const auto loopCondition = currentLoop->loopCondBlock;
    const auto inc = builder.CreateAdd(currentLoop->iValue, builder.getInt32(1));
    builder.CreateStore(inc, currentLoop->iPtr);
    builder.CreateBr(loopCondition);
}
