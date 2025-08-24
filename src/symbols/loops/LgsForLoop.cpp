#include "loops/LgsForLoop.h"
#include "configs/LgsDefinitions.h"
#include "codegen/LgsLLVM.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

json::value LgsForLoop::asJSON() {
    assert(0);
}

Value* LgsForLoop::loadIndex(LgsLLVM& codeGen) const {
    return codeGen.builder.CreateLoad(codeGen.i32Ty(), iPtr);
}

void LgsForLoop::incIndex(LgsLLVM* codeGen) const {
    const auto iValue = loadIndex(*codeGen);
    const auto inc = codeGen->builder.CreateAdd(iValue, codeGen->i32(1));
    codeGen->builder.CreateStore(inc, iPtr);
}

void LgsForLoop::setBlocks(LgsLLVM& codeGen) {
    IRBodyBlock = codeGen.createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen.createBlock(BLOCK_NAME_LOOP_EXIT);
    IRCondBlock = codeGen.createBlock(BLOCK_NAME_LOOP_COND);
}

void LgsForLoop::incAndJumpToCond(LgsLLVM& codeGen) const {
    if (codeGen.lastInstTerminator()) return;
    incIndex(&codeGen);
    codeGen.builder.CreateBr(IRCondBlock);
}

LgsForLoop::~LgsForLoop() {
    if (isFirst) {
        delete isFirst;
        isFirst = nullptr;
    }
    if (isLast) {
        delete isLast;
        isLast = nullptr;
    }
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
    loopVars.clear();
}
