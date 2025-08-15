#include "loops/LgsInfiniteLoop.h"
#include "configs/LgsDefinitions.h"
#include "logos/LgsCodeGen.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsInfiniteLoop::createIRLoop(LgsCodeGen* codeGen) {
    if (!loopVars.empty()) initIndex(codeGen);
    codeGen->branchAndStartBlock(IRBodyBlock);
    if (!loopVars.empty()) {
        const auto iValue = loadIndex(codeGen);
        loopVars.front()->setIRValue(iValue);
    }
    stmtsBlock->createIRValue(codeGen);
}

void LgsInfiniteLoop::incAndJumpToCond(LgsCodeGen* codeGen) const {
    if (codeGen->lastInstTerminator()) return;
    if (!loopVars.empty()) incIndex(codeGen);
    codeGen->builder.CreateBr(IRBodyBlock);
}

void LgsInfiniteLoop::setBlocks(LgsCodeGen* codeGen) {
    IRBodyBlock = codeGen->createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen->createBlock(BLOCK_NAME_LOOP_EXIT);
}
