#include "stmts/LgsIfStmt.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsRuntime.h"
#include "utils/LgsUtils.h"

#define BB_IF_TRUE "if_true"
#define BB_IF_END "if_end"
#define BB_ELSE "else"
#define BB_ELSE_IF "else_if"
#define BB_ELSE_IF_CHECK "else_if_check"

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

void LgsIfStmt::generateSimpleIf(LgsRuntime* runtime) {
    const auto ifCondIR = ifCond->getIRValue(runtime);
    if (!isBranchingNeeded(runtime, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(context, BB_IF_TRUE);
    endBlock = BasicBlock::Create(context, BB_IF_END);
    runtime->builder.CreateCondBr(ifCondIR, trueBlock, endBlock);
    startBlock(runtime, trueBlock);
    ifStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(endBlock);
    startBlock(runtime, endBlock);
}

void LgsIfStmt::generateIfElse(LgsRuntime* runtime) {
    const auto ifCondIR = ifCond->getIRValue(runtime);
    if (!isBranchingNeeded(runtime, ifCondIR)) return;
    const auto trueBlock = BasicBlock::Create(context, BB_IF_TRUE);
    const auto elseBlock = BasicBlock::Create(context, BB_ELSE);
    endBlock = BasicBlock::Create(context, BB_IF_END);
    // if block
    runtime->builder.CreateCondBr(ifCondIR, trueBlock, elseBlock);
    startBlock(runtime, trueBlock);
    ifStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(endBlock);
    // else block
    startBlock(runtime, elseBlock);
    elseStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(endBlock);
    startBlock(runtime, endBlock);
}

void LgsIfStmt::generateComplexIf(LgsRuntime* runtime) {
    const auto ifCondIR = ifCond->getIRValue(runtime);
    if (!isBranchingNeeded(runtime, ifCondIR)) return;
    auto trueBlock = BasicBlock::Create(context, BB_IF_TRUE);
    auto elseIfCheckBlock = BasicBlock::Create(context, BB_ELSE_IF_CHECK);
    const auto elseBlock = BasicBlock::Create(context, BB_ELSE);
    endBlock = BasicBlock::Create(context, BB_IF_END);

    // if block
    runtime->builder.CreateCondBr(ifCondIR, trueBlock, elseIfCheckBlock);
    startBlock(runtime, trueBlock);
    ifStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(endBlock);

    for (int i = 0; i < elseIfConds.size(); ++i) {
        startBlock(runtime, elseIfCheckBlock);
        const auto elseIfCond = elseIfConds[i];
        const auto stmtBlock = elseIfStmtBlocks[i];
        const auto elseIfCondIR = elseIfCond->createIRValue(runtime);
        trueBlock = BasicBlock::Create(context, BB_IF_TRUE);
        const auto lastIter = i == elseIfConds.size() - 1;
        if (lastIter) {
            if (elseStmtBlock) {
                runtime->builder.CreateCondBr(elseIfCondIR, trueBlock, elseBlock);
            } else {
                runtime->builder.CreateCondBr(elseIfCondIR, trueBlock, endBlock);
            }
        } else {
            elseIfCheckBlock = BasicBlock::Create(context, BB_ELSE_IF_CHECK);
            runtime->builder.CreateCondBr(elseIfCondIR, trueBlock, elseIfCheckBlock);
        }
        startBlock(runtime, trueBlock);
        stmtBlock->createIRValue(runtime);
        runtime->builder.CreateBr(endBlock);
    }

    if (elseStmtBlock) {
        startBlock(runtime, elseBlock);
        elseStmtBlock->createIRValue(runtime);
        runtime->builder.CreateBr(endBlock);
    }
    startBlock(runtime, endBlock);
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
