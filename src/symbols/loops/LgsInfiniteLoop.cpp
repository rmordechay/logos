#include "loops/LgsInfiniteLoop.h"
#include "data/LgsDefinitions.h"
#include "codegen/LgsLLVMGen.h"

void LgsInfiniteLoop::incAndJumpToCond(LgsLLVMGen& cg) {
    if (cg.lastInstTerminator()) return;
    cg.builder.CreateBr(IRBodyBlock);
}

Value* LgsInfiniteLoop::loopStart(LgsLLVMGen& cg) {
    return cg.i32Zero();
}

Value* LgsInfiniteLoop::loopEnd(LgsLLVMGen& cg) {
    assert(0);
}

void LgsInfiniteLoop::setBlocks(LgsLLVMGen& cg) {
    IRBodyBlock = cg.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = cg.createBlock(BLOCK_NAME_LOOP_EXIT);
}
