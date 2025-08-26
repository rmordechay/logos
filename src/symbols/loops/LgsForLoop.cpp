#include "loops/LgsForLoop.h"
#include "configs/LgsDefinitions.h"
#include "codegen/LgsLLVM.h"
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

Value* LgsForLoop::loadIndex(LgsLLVM& codeGen) const {
    return codeGen.builder.CreateLoad(codeGen.i32Ty(), iPtr);
}

void LgsForLoop::incIndex(LgsLLVM* codeGen) {
    iValue = loadIndex(*codeGen);
    const auto inc = codeGen->builder.CreateAdd(iValue, codeGen->i32(1));
    codeGen->builder.CreateStore(inc, iPtr);
}

void LgsForLoop::setBlocks(LgsLLVM& codeGen) {
    IRBodyBlock = codeGen.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen.createBlock(BLOCK_NAME_LOOP_EXIT);
    IRCondBlock = codeGen.createBlock(BLOCK_NAME_LOOP_COND);
}

void LgsForLoop::incAndJumpToCond(LgsLLVM& codeGen) {
    if (codeGen.lastInstTerminator()) return;
    incIndex(&codeGen);
    codeGen.builder.CreateBr(IRCondBlock);
}

json::value LgsForLoop::asJSON() {
    assert(0);
}

LgsForLoop::~LgsForLoop() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
    loopVars.clear();
}