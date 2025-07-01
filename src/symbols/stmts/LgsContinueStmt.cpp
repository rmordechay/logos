#include "stmts/LgsContinueStmt.h"



#include <loops/LgsForLoop.h>

void LgsContinueStmt::createIRStmt(LgsModule* runtime) {
    const auto currentLoop = runtime->stack.getLoop();
    const auto loopCondition = currentLoop->IRCondBlock;
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), currentLoop->iPtr);
    const auto inc = runtime->builder.CreateAdd(iValue, runtime->builder.getInt32(1));
    runtime->builder.CreateStore(inc, currentLoop->iPtr);
    runtime->builder.CreateBr(loopCondition);
}
