#include "stmts/LgsContinueStmt.h"

#include "funcs/LgsFunc.h"


#include <loops/LgsForLoop.h>

void LgsContinueStmt::createIRStmt(Module* module) {
    const auto currentLoop = runtime.stack.currentLoop;
    const auto loopCondition = currentLoop->loopCondBlock;
    const auto iValue = builder.CreateLoad(i32Ty, currentLoop->iPtr);
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, currentLoop->iPtr);
    builder.CreateBr(loopCondition);
}
