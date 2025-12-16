#include "loops/LgsForLoop.h"
#include "LgsDefinitions.h"
#include "codegen/LgsCgModule.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"
#include "LgsUtils.h"

using llvm::MDNode;
using llvm::MDString;

void LgsForLoop::setBlocks(LgsCgModule& cg) {
    IRCondBlock = cg.createBlock(BLOCK_LOOP_COND);
    IRBodyBlock = cg.createBlock(BLOCK_LOOP_BODY);
    IRExitBlock = cg.createBlock(BLOCK_LOOP_EXIT);
}

void LgsForLoop::incAndJumpToCond(LgsCgModule& cg) {
    if (cg.lastInstTerminator()) return;
    iValue = cg.builder.CreateLoad(cg.i32Ty(), iPtr);
    const auto inc = cg.builder.CreateAdd(iValue, cg.i32(1));
    cg.store(inc, iPtr);
    const auto br = cg.builder.CreateBr(IRCondBlock);
    const auto mustProgress = MDNode::get(cg.context, MDString::get(cg.context, "llvm.loop.mustprogress"));
    br->setMetadata("llvm.loop", MDNode::getDistinct(cg.context, {mustProgress}));
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
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    for (const auto& loopVar : loopVars) {
        freeStmt(loopVar);
    }
    loopVars.clear();
}
