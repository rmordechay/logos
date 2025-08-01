#include "stmts/LgsContinueStmt.h"
#include <loops/LgsForLoop.h>

void LgsContinueStmt::createIRStmt(LgsCodeGen* codeGen) {
    const auto currentLoop = codeGen->stack.getCurrentLoop();
    const auto loopCondition = currentLoop->IRCondBlock;
    const auto iValue = codeGen->builder.CreateLoad(codeGen->i32Ty(), currentLoop->iPtr);
    const auto inc = codeGen->builder.CreateAdd(iValue, codeGen->i32(1));
    codeGen->builder.CreateStore(inc, currentLoop->iPtr);
    codeGen->builder.CreateBr(loopCondition);
}
