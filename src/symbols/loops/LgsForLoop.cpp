#include "loops/LgsForLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    initIRLoop(codeGen);
    stmtsBlock->createIRValue(codeGen);
    IRLoopPrologue(codeGen);
    codeGen->startBlock(IRExitBlock);
    codeGen->stack.exitScope();
}

void LgsForLoop::setLoopTerminals(LgsCodeGen* codeGen, Value* iValue) {
    if (isFirstVarDec) {
        isFirstVarDec->setIRValue(codeGen->builder.CreateICmpEQ(iValue, loopEnd(codeGen)));
    }
    if (isLastVarDec) {
        const auto decremented = codeGen->builder.CreateSub(loopEnd(codeGen), codeGen->i32(1));
        isLastVarDec->setIRValue(codeGen->builder.CreateICmpEQ(iValue, decremented));
    }
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
