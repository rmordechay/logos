#include "stmts/LgsIfStmt.h"
#include "CodeGenerator.h"

Value* LgsIfStmt::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    if (elseIfConds.size() > 0) {
        computeComplexIf(metadata);
    } else {
        computeSimpleIf(metadata);
    }
    metadata->logosStack.exitScope();
    return nullptr;
}


void LgsIfStmt::computeSimpleIf(CodeGenMetadata* metadata) const {
    auto& builder = metadata->builder;
    const auto ifStartBlock = createBasicBlock(BB_IF_START);
    const auto ifEndBlock = createBasicBlock(BB_IF_END);
    const auto elseBlock = createBasicBlock(BB_ELSE);

    const auto ifCondIR = ifCond->getIRValue(metadata);
    if (!elseStmtBlock) {
        builder.CreateCondBr(ifCondIR, ifStartBlock, ifEndBlock);
    } else {
        builder.CreateCondBr(ifCondIR, ifStartBlock, elseBlock);
    }

    startBlock(metadata, ifStartBlock);
    ifStmtBlock->createIRValue(metadata);
    builder.CreateBr(ifEndBlock);

    if (elseStmtBlock) {
        createElseBlock(metadata, elseBlock, ifEndBlock);
    }
    startBlock(metadata, ifEndBlock);
}

void LgsIfStmt::computeComplexIf(CodeGenMetadata* metadata) const {
    auto& builder = metadata->builder;
    const auto ifStartBlock = createBasicBlock(BB_IF_START);
    auto elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK);
    const auto ifEndBlock = createBasicBlock(BB_IF_END);
    const auto elseBlock = createBasicBlock(BB_ELSE);

    // if block
    const auto ifCondIR = ifCond->getIRValue(metadata);
    builder.CreateCondBr(ifCondIR, ifStartBlock, elseIfCheckBlock);
    startBlock(metadata, ifStartBlock);
    ifStmtBlock->createIRValue(metadata);
    builder.CreateBr(ifEndBlock);

    // else-if blocks
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

    // else block
    if (elseStmtBlock) {
        createElseBlock(metadata, elseBlock, ifEndBlock);
    }

    startBlock(metadata, ifEndBlock);
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
