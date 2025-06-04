#include "stmts/LgsIfStmt.h"

#include "logos/LgsRuntime.h"

void LgsIfStmt::createIRStmt(LgsRuntime* runtime) {
    runtime->stack.enterScope(this);
    if (elseBlock || elseIfConds.size() > 0) {
        computeComplexIf(runtime);
    } else {
        computeSimpleIf(runtime);
    }
    runtime->stack.exitScope(IF_STMT);
}


void LgsIfStmt::computeSimpleIf(LgsRuntime* runtime) {
    ifTrueBlock = createBasicBlock(BB_IF_TRUE, context);
    ifEndBlock = createBasicBlock(BB_IF_END, context);
    elseBlock = createBasicBlock(BB_ELSE, context);

    // if block
    const auto ifCondIR = ifCond->getIRValue(runtime);
    if (!elseStmtBlock) {
        runtime->builder.CreateCondBr(ifCondIR, ifTrueBlock, ifEndBlock);
    } else {
        runtime->builder.CreateCondBr(ifCondIR, ifTrueBlock, elseBlock);
    }
    startBlock(runtime, ifTrueBlock, nullptr);
    ifStmtBlock->createIRValue(runtime);
    if (runtime->builder.GetInsertBlock()->getTerminator()) return;
    runtime->builder.CreateBr(ifEndBlock);

    // else block
    createElseBlock(runtime, elseBlock, ifEndBlock);

    // exit
    startBlock(runtime, ifEndBlock, nullptr);
}

void LgsIfStmt::computeComplexIf(LgsRuntime* runtime) {
    ifTrueBlock = createBasicBlock(BB_IF_TRUE, context);
    elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK, context);
    ifEndBlock = createBasicBlock(BB_IF_END, context);
    elseBlock = createBasicBlock(BB_ELSE, context);

    // if block
    const auto ifCondIR = ifCond->getIRValue(runtime);
    runtime->builder.CreateCondBr(ifCondIR, ifTrueBlock, elseIfCheckBlock);
    startBlock(runtime, ifTrueBlock, nullptr);
    ifStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(ifEndBlock);

    // else if blocks
    createElseIfBlocks(runtime);

    // else block
    createElseBlock(runtime, elseBlock, ifEndBlock);

    // exit
    if (!runtime->builder.GetInsertBlock()->getTerminator()) {
        startBlock(runtime, ifEndBlock, nullptr);
    }
}

void LgsIfStmt::createElseIfBlocks(LgsRuntime* runtime) {
    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        startBlock(runtime, elseIfCheckBlock, nullptr);
        const auto elseIfCondIR = elseIfConds[i]->getIRValue(runtime);
        const auto elseIfStartBlock = createBasicBlock(BB_ELSE_IF_START, context);
        const auto lastIteration = elseIfConds.size() - 1;
        if (i == lastIteration) {
            if (elseStmtBlock) {
                runtime->builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseBlock);
            } else {
                runtime->builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, ifEndBlock);
            }
        } else {
            elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK, context);
            runtime->builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseIfCheckBlock);
        }

        startBlock(runtime, elseIfStartBlock, nullptr);
        elseIfStmtBlocks[i]->createIRValue(runtime);
        runtime->builder.CreateBr(ifEndBlock);
    }
}

void LgsIfStmt::createElseBlock(LgsRuntime* runtime, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const {
    if (!elseStmtBlock) return;
    startBlock(runtime, elseBlock, nullptr);
    elseStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(ifEndBlock);
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
