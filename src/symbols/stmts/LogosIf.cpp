#include "stmts/LogosIf.h"

#include "CodeGenerator.h"

Value* LogosIf::computeIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    if (elseIfConds.size() > 0) {
        computeComplexIf(metadata);
    } else {
        computeSimpleIf(metadata);
    }
    metadata->logosStack.exitScope();
    return nullptr;
}


void LogosIf::computeSimpleIf(CodeGenMetadata* metadata) const {
    auto& builder = metadata->builder;
    const auto ifStartBlock = getBasicBlock(BB_IF_START);
    const auto ifEndBlock = getBasicBlock(BB_IF_END);
    const auto elseBlock = getBasicBlock(BB_ELSE);

    const auto ifCondIR = ifCond->writeIRValue(metadata);
    if (elseStmtBlock) {
        builder.CreateCondBr(ifCondIR, ifStartBlock, elseBlock);
    } else {
        builder.CreateCondBr(ifCondIR, ifStartBlock, ifEndBlock);
    }

    startBlock(metadata, ifStartBlock);
    ifStmtBlock->writeIRValue(metadata);
    builder.CreateBr(ifEndBlock);

    if (elseStmtBlock) {
        createElseBlock(metadata, elseBlock, ifEndBlock);
    }
    startBlock(metadata, ifEndBlock);
}

void LogosIf::createElseBlock(CodeGenMetadata* metadata, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const {
    startBlock(metadata, elseBlock);
    elseStmtBlock->writeIRValue(metadata);
    metadata->builder.CreateBr(ifEndBlock);
}

void LogosIf::computeComplexIf(CodeGenMetadata* metadata) const {
    auto& builder = metadata->builder;
    const auto ifStartBlock = getBasicBlock(BB_IF_START);
    auto elseIfCheckBlock = getBasicBlock(BB_ELSE_IF_CHECK);
    const auto ifEndBlock = getBasicBlock(BB_IF_END);
    const auto elseBlock = getBasicBlock(BB_ELSE);

    // if block
    const auto ifCondIR = ifCond->writeIRValue(metadata);
    builder.CreateCondBr(ifCondIR, ifStartBlock, elseIfCheckBlock);
    startBlock(metadata, ifStartBlock);
    ifStmtBlock->writeIRValue(metadata);
    builder.CreateBr(ifEndBlock);

    // else-if blocks
    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        startBlock(metadata, elseIfCheckBlock);
        const auto elseIfCondIR = elseIfConds[i]->writeIRValue(metadata);
        const auto elseIfStartBlock = getBasicBlock(BB_ELSE_IF_START);
        const auto lastIteration = elseIfConds.size() - 1;
        if (i == lastIteration) {
            if (elseStmtBlock) {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseBlock);
            } else {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, ifEndBlock);
            }
        } else {
            elseIfCheckBlock = getBasicBlock(BB_ELSE_IF_CHECK);
            builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseIfCheckBlock);
        }

        startBlock(metadata, elseIfStartBlock);
        elseIfStmtBlocks[i]->writeIRValue(metadata);
        builder.CreateBr(ifEndBlock);
    }

    // else block
    if (elseStmtBlock) {
        createElseBlock(metadata, elseBlock, ifEndBlock);
    }

    startBlock(metadata, ifEndBlock);
}

LogosIf::~LogosIf() {
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
