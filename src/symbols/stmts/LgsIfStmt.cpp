#include "stmts/LgsIfStmt.h"
#include "codegen/CodegenMetadata.h"

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
    ifTrueBlock = createBasicBlock(BB_IF_TRUE);
    ifEndBlock = createBasicBlock(BB_IF_END);
    elseBlock = createBasicBlock(BB_ELSE);

    // if block
    const auto ifCondIR = ifCond->getIRValue(runtime);
    if (!elseStmtBlock) {
        builder.CreateCondBr(ifCondIR, ifTrueBlock, ifEndBlock);
    } else {
        builder.CreateCondBr(ifCondIR, ifTrueBlock, elseBlock);
    }
    startBlock(ifTrueBlock, nullptr);
    ifStmtBlock->createIRValue(runtime);
    if (builder.GetInsertBlock()->getTerminator()) return;
    builder.CreateBr(ifEndBlock);

    // else block
    createElseBlock(runtime, elseBlock, ifEndBlock);

    // exit
    startBlock(ifEndBlock, nullptr);
}

void LgsIfStmt::computeComplexIf(LgsRuntime* runtime) {
    ifTrueBlock = createBasicBlock(BB_IF_TRUE);
    elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK);
    ifEndBlock = createBasicBlock(BB_IF_END);
    elseBlock = createBasicBlock(BB_ELSE);

    // if block
    const auto ifCondIR = ifCond->getIRValue(runtime);
    builder.CreateCondBr(ifCondIR, ifTrueBlock, elseIfCheckBlock);
    startBlock(ifTrueBlock, nullptr);
    ifStmtBlock->createIRValue(runtime);
    builder.CreateBr(ifEndBlock);

    // else if blocks
    createElseIfBlocks(runtime);

    // else block
    createElseBlock(runtime, elseBlock, ifEndBlock);

    // exit
    if (!builder.GetInsertBlock()->getTerminator()) {
        startBlock(ifEndBlock, nullptr);
    }
}

void LgsIfStmt::createElseIfBlocks(LgsRuntime* runtime) {
    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        startBlock(elseIfCheckBlock, nullptr);
        const auto elseIfCondIR = elseIfConds[i]->getIRValue(runtime);
        const auto elseIfStartBlock = createBasicBlock(BB_ELSE_IF_START);
        const auto lastIteration = elseIfConds.size() - 1;
        if (i == lastIteration) {
            if (elseStmtBlock) {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseBlock);
            } else {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, ifEndBlock);
            }
        } else {
            elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK);
            builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseIfCheckBlock);
        }

        startBlock(elseIfStartBlock, nullptr);
        elseIfStmtBlocks[i]->createIRValue(runtime);
        builder.CreateBr(ifEndBlock);
    }
}

void LgsIfStmt::createElseBlock(LgsRuntime* runtime, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const {
    if (!elseStmtBlock) return;
    startBlock(elseBlock, nullptr);
    elseStmtBlock->createIRValue(runtime);
    builder.CreateBr(ifEndBlock);
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
