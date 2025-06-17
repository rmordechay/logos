#include "stmts/LgsIfStmt.h"
#include "logos/LgsRuntime.h"
#include "utils/LgsUtils.h"

void LgsIfStmt::createIRStmt(LgsRuntime* runtime) {
    runtime->stack.enterScope(IF_SCOPE, this);
    if (elseIfConds.empty()) {
        if (elseStmtBlock) {
            generateIfElse(runtime);
        } else {
            generateSimpleIf(runtime);
        }
    } else {
        generateComplexIf(runtime);
    }
    runtime->stack.exitScope(IF_SCOPE);
}

void LgsIfStmt::generateSimpleIf(LgsRuntime* runtime) const {
    const auto ifCondIR = ifCond->getIRValue(runtime);
    if (!isBranchingNeeded(runtime, ifCondIR)) return;
    const auto trueBlock = createBasicBlock(BB_IF_TRUE, context);
    const auto endBlock = createBasicBlock(BB_IF_END, context);
    // if block
    runtime->builder.CreateCondBr(ifCondIR, trueBlock, endBlock);
    startBlock(runtime, trueBlock);
    ifStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(endBlock);
    // exit
    startBlock(runtime, endBlock);
}

void LgsIfStmt::generateIfElse(LgsRuntime* runtime) {
    const auto ifCondIR = ifCond->getIRValue(runtime);
    if (!isBranchingNeeded(runtime, ifCondIR)) return;
    const auto trueBlock = createBasicBlock(BB_IF_TRUE, context);
    const auto elseBlock = createBasicBlock(BB_ELSE, context);
    endBlock = createBasicBlock(BB_IF_END, context);
    runtime->builder.CreateCondBr(ifCondIR, trueBlock, elseBlock);
    startBlock(runtime, trueBlock);
    ifStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(endBlock);
    startBlock(runtime, elseBlock);
    elseStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(endBlock);
    startBlock(runtime, endBlock);
}

void LgsIfStmt::generateComplexIf(LgsRuntime* runtime) {

}

bool LgsIfStmt::isBranchingNeeded(LgsRuntime* runtime, Value* ifCondIR) const {
    if (const auto* constBool = dyn_cast<ConstantInt>(ifCondIR)) {
        if (constBool->isOne()) {
            ifStmtBlock->createIRValue(runtime);
        }
        return false;
    }
    return true;
}

LgsIfStmt::~LgsIfStmt() {
    delete ifCond;
    delete ifStmtBlock;
    for (const auto &elseIfCond : elseIfConds) {
        delete elseIfCond;
    }
    for (const auto &elseIfStmtBlock : elseIfStmtBlocks) {
        delete elseIfStmtBlock;
    }
    if (elseStmtBlock) {
        delete elseStmtBlock;
    }
}
