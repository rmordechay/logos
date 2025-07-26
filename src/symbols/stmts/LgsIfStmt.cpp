#include "stmts/LgsIfStmt.h"

#include "data/LgsDefinitions.h"
#include "logos/LgsModule.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

void LgsIfStmt::createIRStmt(LgsModule* module) {
    module->stack.enterScope(IF_SCOPE, this);
    if (elseIfConds.empty()) {
        if (!elseStmtBlock) {
            generateSimpleIf(module);
        } else {
            generateIfElse(module);
        }
    } else {
        generateComplexIf(module);
    }
    module->stack.exitScope();
}

void LgsIfStmt::generateSimpleIf(LgsModule* module) const {
    const auto ifCondIR = ifCond->getIRValue(module);
    if (!shouldBranch(module, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(module->context, BLOCK_NAME_IF_TRUE);
    const auto endBlock = BasicBlock::Create(module->context, BLOCK_NAME_IF_END);
    module->builder.CreateCondBr(ifCondIR, trueBlock, endBlock);
    startBlock(module, trueBlock);
    ifStmtBlock->createIRValue(module);
    branchToBlock(module, endBlock);
    startBlock(module, endBlock);
}

void LgsIfStmt::generateIfElse(LgsModule* module) const {
    const auto ifCondIR = ifCond->getIRValue(module);
    if (!shouldBranch(module, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(module->context, BLOCK_NAME_IF_TRUE);
    const auto elseBlock = BasicBlock::Create(module->context, BLOCK_NAME_ELSE);
    const auto endBlock = BasicBlock::Create(module->context, BLOCK_NAME_IF_END);
    // if block
    module->builder.CreateCondBr(ifCondIR, trueBlock, elseBlock);
    startBlock(module, trueBlock);
    ifStmtBlock->createIRValue(module);
    branchToBlock(module, endBlock);
    // else block
    startBlock(module, elseBlock);
    elseStmtBlock->createIRValue(module);
    branchToBlock(module, endBlock);
    startBlock(module, endBlock);
}

void LgsIfStmt::generateComplexIf(LgsModule* module) const {
    const auto ifCondIR = ifCond->getIRValue(module);
    if (!shouldBranch(module, ifCondIR)) return;
    auto trueBlock = BasicBlock::Create(module->context, BLOCK_NAME_IF_TRUE);
    auto elseIfCheckBlock = BasicBlock::Create(module->context, BLOCK_NAME_ELSE_IF_CHECK);
    const auto elseBlock = BasicBlock::Create(module->context, BLOCK_NAME_ELSE);
    const auto endBlock = BasicBlock::Create(module->context, BLOCK_NAME_IF_END);

    // if block
    module->builder.CreateCondBr(ifCondIR, trueBlock, elseIfCheckBlock);
    startBlock(module, trueBlock);
    ifStmtBlock->createIRValue(module);
    branchToBlock(module, endBlock);

    for (int i = 0; i < elseIfConds.size(); ++i) {
        startBlock(module, elseIfCheckBlock);
        const auto elseIfCond = elseIfConds[i];
        const auto stmtBlock = elseIfStmtBlocks[i];
        const auto elseIfCondIR = elseIfCond->getIRValue(module);
        trueBlock = BasicBlock::Create(module->context, BLOCK_NAME_ELSE_IF);
        const auto lastIter = i == elseIfConds.size() - 1;
        if (lastIter) {
            if (elseStmtBlock) {
                module->builder.CreateCondBr(elseIfCondIR, trueBlock, elseBlock);
            } else {
                module->builder.CreateCondBr(elseIfCondIR, trueBlock, endBlock);
            }
        } else {
            elseIfCheckBlock = BasicBlock::Create(module->context, BLOCK_NAME_ELSE_IF_CHECK);
            module->builder.CreateCondBr(elseIfCondIR, trueBlock, elseIfCheckBlock);
        }
        startBlock(module, trueBlock);
        stmtBlock->createIRValue(module);
        branchToBlock(module, endBlock);
    }

    if (elseStmtBlock) {
        startBlock(module, elseBlock);
        elseStmtBlock->createIRValue(module);
        branchToBlock(module, endBlock);
    }
    startBlock(module, endBlock);
}

bool LgsIfStmt::shouldBranch(LgsModule* module, Value* ifCondIR) const {
    if (const auto* constBool = dyn_cast<ConstantInt>(ifCondIR)) {
        if (constBool->isOne()) {
            ifStmtBlock->createIRValue(module);
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