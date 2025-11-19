#include "loops/LgsForLoop.h"
#include "LgsDefinitions.h"
#include "codegen/LgsLLVMGen.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"
#include "LgsUtils.h"

void LgsForLoop::setBlocks(LgsLLVMGen& cg) {
    IRCondBlock = cg.createBlock(BLOCK_NAME_LOOP_COND);
    IRBodyBlock = cg.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = cg.createBlock(BLOCK_NAME_LOOP_EXIT);
}

void LgsForLoop::incAndJumpToCond(LgsLLVMGen& cg) {
    const auto currentValue = cg.builder.CreateLoad(cg.i32Ty(), iPtr);
    const auto constOne = ConstantInt::get(currentValue->getType(), 1);
    const auto incValue = cg.builder.CreateAdd(currentValue, constOne);
    const auto decValue = cg.builder.CreateSub(currentValue, constOne);
    const auto newValue = cg.builder.CreateSelect(isReversed, incValue, decValue);
    cg.builder.CreateStore(newValue, iPtr);
    cg.builder.CreateBr(IRCondBlock);
}

LgsForeachLoop* LgsForLoop::asForeachLoop() {
    return dynamic_cast<LgsForeachLoop*>(this);
}

LgsRangeLoop* LgsForLoop::asRangeLoop() {
    return dynamic_cast<LgsRangeLoop*>(this);
}

LgsInfiniteLoop* LgsForLoop::asInfiniteLoop() {
    return dynamic_cast<LgsInfiniteLoop*>(this);
}

LgsWhileLoop* LgsForLoop::asWhileLoop() {
    return dynamic_cast<LgsWhileLoop*>(this);
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        freeStmt(loopVar);
    }
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    loopVars.clear();
}
