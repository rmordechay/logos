#include "stmts/LgsContinueStmt.h"

#include "logos/LgsRuntime.h"

#include <loops/LgsForLoop.h>

void LgsContinueStmt::createIRStmt(LgsRuntime* runtime) {
    const auto currentLoop = runtime->stack.currentLoop;
    const auto loopCondition = currentLoop->loopCondBlock;
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), currentLoop->iPtr);
    const auto inc = runtime->builder.CreateAdd(iValue, runtime->builder.getInt32(1));
    runtime->builder.CreateStore(inc, currentLoop->iPtr);
    runtime->builder.CreateBr(loopCondition);
}
