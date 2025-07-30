#include "stmts/LgsIfStmt.h"
#include "configs/LgsDefinitions.h"
#include "logos/LgsCodeGen.h"

void LgsIfStmt::createIRStmt(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(IF_SCOPE, this);
    if (elseIfConds.empty()) {
        if (!elseStmtBlock) {
            generateSimpleIf(codeGen);
        } else {
            generateIfElse(codeGen);
        }
    } else {
        generateComplexIf(codeGen);
    }
    codeGen->stack.exitScope();
}

void LgsIfStmt::generateSimpleIf(LgsCodeGen* codeGen) const {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_IF_TRUE);
    const auto endBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_IF_END);
    codeGen->builder.CreateCondBr(ifCondIR, trueBlock, endBlock);
    codeGen->startBlock(trueBlock);
    ifStmtBlock->createIRValue(codeGen);
    codeGen->branchToBlock(endBlock);
    codeGen->startBlock(endBlock);
}

void LgsIfStmt::generateIfElse(LgsCodeGen* codeGen) const {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_IF_TRUE);
    const auto elseBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_ELSE);
    const auto endBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_IF_END);
    // if block
    codeGen->builder.CreateCondBr(ifCondIR, trueBlock, elseBlock);
    codeGen->startBlock(trueBlock);
    ifStmtBlock->createIRValue(codeGen);
    codeGen->branchToBlock(endBlock);
    // else block
    codeGen->startBlock(elseBlock);
    elseStmtBlock->createIRValue(codeGen);
    codeGen->branchToBlock(endBlock);
    codeGen->startBlock(endBlock);
}

void LgsIfStmt::generateComplexIf(LgsCodeGen* codeGen) const {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    auto trueBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_IF_TRUE);
    auto elseIfCheckBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_ELSE_IF_CHECK);
    const auto elseBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_ELSE);
    const auto endBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_IF_END);

    // if block
    codeGen->builder.CreateCondBr(ifCondIR, trueBlock, elseIfCheckBlock);
    codeGen->startBlock(trueBlock);
    ifStmtBlock->createIRValue(codeGen);
    codeGen->branchToBlock(endBlock);

    for (int i = 0; i < elseIfConds.size(); ++i) {
        codeGen->startBlock(elseIfCheckBlock);
        const auto elseIfCond = elseIfConds[i];
        const auto stmtBlock = elseIfStmtBlocks[i];
        const auto elseIfCondIR = elseIfCond->getIRValue(codeGen);
        trueBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_ELSE_IF);
        const auto lastIter = i == elseIfConds.size() - 1;
        if (lastIter) {
            if (elseStmtBlock) {
                codeGen->builder.CreateCondBr(elseIfCondIR, trueBlock, elseBlock);
            } else {
                codeGen->builder.CreateCondBr(elseIfCondIR, trueBlock, endBlock);
            }
        } else {
            elseIfCheckBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_ELSE_IF_CHECK);
            codeGen->builder.CreateCondBr(elseIfCondIR, trueBlock, elseIfCheckBlock);
        }
        codeGen->startBlock(trueBlock);
        stmtBlock->createIRValue(codeGen);
        codeGen->branchToBlock(endBlock);
    }

    if (elseStmtBlock) {
        codeGen->startBlock(elseBlock);
        elseStmtBlock->createIRValue(codeGen);
        codeGen->branchToBlock(endBlock);
    }
    codeGen->startBlock(endBlock);
}

bool LgsIfStmt::shouldBranch(LgsCodeGen* codeGen, Value* ifCondIR) const {
    if (const auto* constBool = dyn_cast<ConstantInt>(ifCondIR)) {
        if (constBool->isOne()) {
            ifStmtBlock->createIRValue(codeGen);
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