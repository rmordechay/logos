#include "stmts/LgsIfStmt.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsModule.h"
#include "utils/LgsUtils.h"

#define BB_IF_TRUE "if_true"
#define BB_IF_END "if_end"
#define BB_ELSE "else"
#define BB_ELSE_IF "else_if"
#define BB_ELSE_IF_CHECK "else_if_check"

void LgsIfStmt::createIRStmt(LgsModule* module) {
    module->stack.enterScope(IF_SCOPE, this);
    if (elseIfConds.empty()) {
        if (elseStmtBlock) {
            generateIfElse(module);
        } else {
            generateSimpleIf(module);
        }
    } else {
        generateComplexIf(module);
    }
    module->stack.exitScope(IF_SCOPE);
}

void LgsIfStmt::generateSimpleIf(LgsModule* module) {
    const auto ifCondIR = ifCond->getIRValue(module);
    if (!isBranchingNeeded(module, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(module->context, BB_IF_TRUE);
    endBlock = BasicBlock::Create(module->context, BB_IF_END);
    module->builder.CreateCondBr(ifCondIR, trueBlock, endBlock);
    startBlock(module, trueBlock);
    ifStmtBlock->createIRValue(module);
    module->builder.CreateBr(endBlock);
    startBlock(module, endBlock);
}

void LgsIfStmt::generateIfElse(LgsModule* module) {
    const auto ifCondIR = ifCond->getIRValue(module);
    if (!isBranchingNeeded(module, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(module->context, BB_IF_TRUE);
    const auto elseBlock = BasicBlock::Create(module->context, BB_ELSE);
    endBlock = BasicBlock::Create(module->context, BB_IF_END);
    // if block
    module->builder.CreateCondBr(ifCondIR, trueBlock, elseBlock);
    startBlock(module, trueBlock);
    ifStmtBlock->createIRValue(module);
    module->builder.CreateBr(endBlock);
    // else block
    startBlock(module, elseBlock);
    elseStmtBlock->createIRValue(module);
    module->builder.CreateBr(endBlock);
    startBlock(module, endBlock);
}

void LgsIfStmt::generateComplexIf(LgsModule* module) {
    const auto ifCondIR = ifCond->getIRValue(module);
    if (!isBranchingNeeded(module, ifCondIR)) return;
    auto trueBlock = BasicBlock::Create(module->context, BB_IF_TRUE);
    auto elseIfCheckBlock = BasicBlock::Create(module->context, BB_ELSE_IF_CHECK);
    const auto elseBlock = BasicBlock::Create(module->context, BB_ELSE);
    endBlock = BasicBlock::Create(module->context, BB_IF_END);

    // if block
    module->builder.CreateCondBr(ifCondIR, trueBlock, elseIfCheckBlock);
    startBlock(module, trueBlock);
    ifStmtBlock->createIRValue(module);
    module->builder.CreateBr(endBlock);

    for (int i = 0; i < elseIfConds.size(); ++i) {
        startBlock(module, elseIfCheckBlock);
        const auto elseIfCond = elseIfConds[i];
        const auto stmtBlock = elseIfStmtBlocks[i];
        const auto elseIfCondIR = elseIfCond->createIRValue(module);
        trueBlock = BasicBlock::Create(module->context, BB_IF_TRUE);
        const auto lastIter = i == elseIfConds.size() - 1;
        if (lastIter) {
            if (elseStmtBlock) {
                module->builder.CreateCondBr(elseIfCondIR, trueBlock, elseBlock);
            } else {
                module->builder.CreateCondBr(elseIfCondIR, trueBlock, endBlock);
            }
        } else {
            elseIfCheckBlock = BasicBlock::Create(module->context, BB_ELSE_IF_CHECK);
            module->builder.CreateCondBr(elseIfCondIR, trueBlock, elseIfCheckBlock);
        }
        startBlock(module, trueBlock);
        stmtBlock->createIRValue(module);
        module->builder.CreateBr(endBlock);
    }

    if (elseStmtBlock) {
        startBlock(module, elseBlock);
        elseStmtBlock->createIRValue(module);
        module->builder.CreateBr(endBlock);
    }
    startBlock(module, endBlock);
}

bool LgsIfStmt::isBranchingNeeded(LgsModule* module, Value* ifCondIR) const {
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
