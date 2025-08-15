#include "loops/LgsForLoop.h"
#include "configs/LgsDefinitions.h"
#include "logos/LgsCodeGen.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRValue(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    setBlocks(codeGen);
    createIRLoop(codeGen);
    incAndJumpToCond(codeGen);
    codeGen->startBlock(IRExitBlock);
    codeGen->stack.exitScope();
}

void LgsForLoop::initIndex(LgsCodeGen* codeGen) {
    iPtr = codeGen->builder.CreateAlloca(codeGen->i32Ty());
    codeGen->builder.CreateStore(codeGen->i32Zero(), iPtr);
}

Value* LgsForLoop::loadIndex(LgsCodeGen* codeGen) const {
    return codeGen->builder.CreateLoad(codeGen->i32Ty(), iPtr);
}

void LgsForLoop::incIndex(LgsCodeGen* codeGen) const {
    const auto iValue = loadIndex(codeGen);
    const auto inc = codeGen->builder.CreateAdd(iValue, codeGen->i32(1));
    codeGen->builder.CreateStore(inc, iPtr);
}

void LgsForLoop::setBlocks(LgsCodeGen* codeGen) {
    IRBodyBlock = codeGen->createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen->createBlock(BLOCK_NAME_LOOP_EXIT);
    IRCondBlock = codeGen->createBlock(BLOCK_NAME_LOOP_COND);
}

void LgsForLoop::incAndJumpToCond(LgsCodeGen* codeGen) const {
    if (codeGen->lastInstTerminator()) return;
    incIndex(codeGen);
    codeGen->builder.CreateBr(IRCondBlock);
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
