#include "loops/LgsWhileLoop.h"

#include "exprs/LgsExpr.h"
#include "logos/LgsCodeGen.h"
#include "stmts/LgsStmtsBlock.h"

void LgsWhileLoop::createIRLoop(LgsCodeGen* codeGen) {
    codeGen->builder.CreateBr(IRCondBlock);
    // Condition
    codeGen->startBlock(IRCondBlock);
    const auto condition = condExpr->getIRValue(codeGen);
    codeGen->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);
    // Body
    codeGen->startBlock(IRBodyBlock);
    stmtsBlock->createIRValue(codeGen);
}

void LgsWhileLoop::incAndJumpToCond(LgsCodeGen* codeGen) const {
    if (codeGen->lastInstTerminator()) return;
    codeGen->builder.CreateBr(IRCondBlock);
}
