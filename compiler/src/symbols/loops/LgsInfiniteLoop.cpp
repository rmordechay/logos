#include "loops/LgsInfiniteLoop.h"

#include <assert.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include "LgsDefinitions.h"
#include "codegen/LgsCodeGen.h"

void LgsInfiniteLoop::incAndJumpToCond(LgsCodeGen& cg) {
    if (cg.lastInstTerminator()) return;
    cg.builder.CreateBr(IRBodyBlock);
}

Value* LgsInfiniteLoop::loopStart(LgsCodeGen& cg) {
    return cg.zero32();
}

Value* LgsInfiniteLoop::loopEnd(LgsCodeGen& cg) {
    assert(0);
}

void LgsInfiniteLoop::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

void LgsInfiniteLoop::setBlocks(LgsCodeGen& cg) {
    IRBodyBlock = cg.createBlock(BLOCK_LOOP_BODY);
    IRExitBlock = cg.createBlock(BLOCK_LOOP_EXIT);
}
