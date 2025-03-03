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
    const auto currentFunc = metadata->logosStack.currentFunc;
    auto& builder = metadata->builder;
    const auto ifStartBlock = BasicBlock::Create(context, "if.start");
    const auto ifEndBlock = BasicBlock::Create(context, "if.end");
    const auto elseBlock = BasicBlock::Create(context, "else");

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
    const auto ifStartBlock = BasicBlock::Create(context, "if.start");
    auto elseIfCheckBlock = BasicBlock::Create(context, "else.if.check");
    const auto ifEndBlock = BasicBlock::Create(context, "if.end");
    const auto elseBlock = BasicBlock::Create(context, "else");

    // Handle if block
    const auto ifCondIR = ifCond->writeIRValue(metadata);
    builder.CreateCondBr(ifCondIR, ifStartBlock, elseIfCheckBlock);
    startBlock(metadata, ifStartBlock);
    ifStmtBlock->writeIRValue(metadata);
    builder.CreateBr(ifEndBlock);

    // Handle else-if blocks
    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        startBlock(metadata, elseIfCheckBlock);
        const auto elseIfCondIR = elseIfConds[i]->writeIRValue(metadata);
        const auto elseIfStartBlock = BasicBlock::Create(context, "else.if.start");
        const auto lastIteration = elseIfConds.size() - 1;
        if (i == lastIteration) {
            if (elseStmtBlock) {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseBlock);
            } else {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, ifEndBlock);
            }
        } else {
            elseIfCheckBlock = BasicBlock::Create(context, "else.if.check");
            builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseIfCheckBlock);
        }

        startBlock(metadata, elseIfStartBlock);
        elseIfStmtBlocks[i]->writeIRValue(metadata);
        builder.CreateBr(ifEndBlock);
    }

    // Handle else block if exists
    if (elseStmtBlock) {
        createElseBlock(metadata, elseBlock, ifEndBlock);
    }

    startBlock(metadata, ifEndBlock);
}

void LogosIf::startBlock(CodeGenMetadata* metadata, BasicBlock* const block) {
    const auto currentFunc = metadata->logosStack.currentFunc;
    auto& builder = metadata->builder;
    block->insertInto(currentFunc);
    builder.SetInsertPoint(block);
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
