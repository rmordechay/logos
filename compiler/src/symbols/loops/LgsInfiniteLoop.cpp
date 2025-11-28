#include "loops/LgsInfiniteLoop.h"
#include "LgsDefinitions.h"
#include "codegen/LgsCgModule.h"

void LgsInfiniteLoop::incAndJumpToCond(LgsCgModule& cg) {
    if (cg.lastInstTerminator()) return;
    cg.builder.CreateBr(IRBodyBlock);
}

Value* LgsInfiniteLoop::loopStart(LgsCgModule& cg) {
    return cg.i32Zero();
}

Value* LgsInfiniteLoop::loopEnd(LgsCgModule& cg) {
    assert(0);
}

void LgsInfiniteLoop::setBlocks(LgsCgModule& cg) {
    IRBodyBlock = cg.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = cg.createBlock(BLOCK_NAME_LOOP_EXIT);
}
