#include "loops/LgsInfiniteLoop.h"
#include "configs/LgsDefinitions.h"
#include "codegen/LgsLLVM.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsInfiniteLoop::incAndJumpToCond(LgsLLVM& codeGen) const {
    if (codeGen.lastInstTerminator()) return;
    if (!loopVars.empty()) incIndex(&codeGen);
    codeGen.builder.CreateBr(IRBodyBlock);
}

void LgsInfiniteLoop::setBlocks(LgsLLVM& codeGen) {
    IRBodyBlock = codeGen.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen.createBlock(BLOCK_NAME_LOOP_EXIT);
}
