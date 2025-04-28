#include "stmts/LgsIfStmt.h"

Value* LgsIfStmt::createIRValue(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope();
    if (elseIfConds.size() > 0) {
        computeComplexIf(metadata);
    } else {
        computeSimpleIf(metadata);
    }
    metadata->lgsStack.exitScope();
    return nullptr;
}


void LgsIfStmt::computeSimpleIf(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    ifTrueBlock = createBasicBlock(BB_IF_TRUE);
    ifEndBlock = createBasicBlock(BB_IF_END);
    elseBlock = createBasicBlock(BB_ELSE);
    assert(ifCond);
    const auto ifCondIR = ifCond->getIRValue(metadata);
    if (!elseStmtBlock) {
        builder.CreateCondBr(ifCondIR, ifTrueBlock, ifEndBlock);
    } else {
        builder.CreateCondBr(ifCondIR, ifTrueBlock, elseBlock);
    }

    startBlock(metadata, ifTrueBlock);
    ifStmtBlock->createIRValue(metadata);
    if (!builder.GetInsertBlock()->getTerminator()) {
        builder.CreateBr(ifEndBlock);
    }

    if (elseStmtBlock) {
        createElseBlock(metadata, elseBlock, ifEndBlock);
    }

    startBlock(metadata, ifEndBlock);
}

void LgsIfStmt::computeComplexIf(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    ifTrueBlock = createBasicBlock(BB_IF_TRUE);
    elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK);
    ifEndBlock = createBasicBlock(BB_IF_END);
    elseBlock = createBasicBlock(BB_ELSE);

    // if block
    const auto ifCondIR = ifCond->getIRValue(metadata);
    builder.CreateCondBr(ifCondIR, ifTrueBlock, elseIfCheckBlock);
    startBlock(metadata, ifTrueBlock);
    ifStmtBlock->createIRValue(metadata);
    builder.CreateBr(ifEndBlock);

    createElseIfBlocks(metadata);
    if (elseStmtBlock) {
        createElseBlock(metadata, elseBlock, ifEndBlock);
    }
    if (!builder.GetInsertBlock()->getTerminator()) {
        startBlock(metadata, ifEndBlock);
    }
}

void LgsIfStmt::createElseIfBlocks(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        startBlock(metadata, elseIfCheckBlock);
        const auto elseIfCondIR = elseIfConds[i]->getIRValue(metadata);
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

        startBlock(metadata, elseIfStartBlock);
        elseIfStmtBlocks[i]->createIRValue(metadata);
        builder.CreateBr(ifEndBlock);
    }
}

void LgsIfStmt::createElseBlock(CodeGenMetadata* metadata, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const {
    startBlock(metadata, elseBlock);
    elseStmtBlock->createIRValue(metadata);
    metadata->builder.CreateBr(ifEndBlock);
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
