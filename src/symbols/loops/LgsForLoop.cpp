#include "loops/LgsForLoop.h"
#include "data/LgsDefinitions.h"
#include "codegen/LgsLLVMGen.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

LgsForeachLoop* LgsForLoop::asForeachLoop() { return dynamic_cast<LgsForeachLoop*>(this);}
LgsRangeLoop* LgsForLoop::asRangeLoop() { return dynamic_cast<LgsRangeLoop*>(this);}
LgsInfiniteLoop* LgsForLoop::asInfiniteLoop() { return dynamic_cast<LgsInfiniteLoop*>(this);}
LgsWhileLoop* LgsForLoop::asWhileLoop() { return dynamic_cast<LgsWhileLoop*>(this);}

Value* LgsForLoop::loadIndex(LgsLLVMGen& cg) const {
    return cg.builder.CreateLoad(cg.sizeTy(), iPtr);
}

void LgsForLoop::setBlocks(LgsLLVMGen& cg) {
    IRCondBlock = cg.createBlock(BLOCK_NAME_LOOP_COND);
    IRBodyBlock = cg.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = cg.createBlock(BLOCK_NAME_LOOP_EXIT);
}

void LgsForLoop::incAndJumpToCond(LgsLLVMGen& cg) {
    if (cg.lastInstTerminator()) return;
    iValue = loadIndex(cg);
    const auto inc = cg.builder.CreateAdd(iValue, cg.usize(1));
    cg.builder.CreateStore(inc, iPtr);
    cg.builder.CreateBr(IRCondBlock);
}

LgsForLoop::~LgsForLoop() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    for (const auto& loopVar : loopVars) {
        // delete loopVar;
    }
    loopVars.clear();
}