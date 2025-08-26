#include "loops/LgsInfiniteLoop.h"
#include "configs/LgsDefinitions.h"
#include "codegen/LgsLLVM.h"
#include "stmts/LgsVarDec.h"

void LgsInfiniteLoop::incAndJumpToCond(LgsLLVM& codeGen) {
    if (codeGen.lastInstTerminator()) return;
    if (!loopVars.empty()) incIndex(&codeGen);
    codeGen.builder.CreateBr(IRBodyBlock);
}

Value* LgsInfiniteLoop::loopStart(LgsLLVM& codeGen) {
    return codeGen.i32Zero();
}

Value* LgsInfiniteLoop::loopEnd(LgsLLVM& codeGen) {
    assert(0);
}

void LgsInfiniteLoop::setBlocks(LgsLLVM& codeGen) {
    IRBodyBlock = codeGen.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen.createBlock(BLOCK_NAME_LOOP_EXIT);
}
