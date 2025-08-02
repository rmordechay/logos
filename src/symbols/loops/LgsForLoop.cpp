#include "loops/LgsForLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    initIRLoop(codeGen);
    stmtsBlock->createIRValue(codeGen);
    incIndex(codeGen);
    codeGen->startBlock(IRExitBlock);
    codeGen->stack.exitScope();
}

void LgsForLoop::initIndex(LgsCodeGen* codeGen) {
    iPtr = codeGen->builder.CreateAlloca(codeGen->i32Ty());
    codeGen->builder.CreateStore(codeGen->i32Zero(), iPtr);
}

LoadInst* LgsForLoop::loadIndex(LgsCodeGen* codeGen) const {
    return codeGen->builder.CreateLoad(codeGen->i32Ty(), iPtr);
}

void LgsForLoop::incIndex(LgsCodeGen* codeGen) const {
    if (codeGen->lastInstTerminator()) return;
    const auto iValue = loadIndex(codeGen);
    const auto inc = codeGen->builder.CreateAdd(iValue, codeGen->i32(1));
    codeGen->builder.CreateStore(inc, iPtr);
    codeGen->builder.CreateBr(IRCondBlock);
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
    if (isFirstVarDec) {
        delete isFirstVarDec;
    }
    if (isLastVarDec) {
        delete isLastVarDec;
    }
}
