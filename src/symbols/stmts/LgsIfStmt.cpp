#include "stmts/LgsIfStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsCodeGen.h"

void LgsIfStmt::createIRStmt(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(IF_SCOPE, this);
    if (elseIfConds.empty()) {
        if (!elseStmtsBlock) {
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
    const auto trueBlock = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    const auto endBlock = codeGen->createBlock(BLOCK_NAME_IF_END);
    codeGen->builder.CreateCondBr(ifCondIR, trueBlock, endBlock);
    codeGen->startBlock(trueBlock);
    ifStmtsBlock->createIRValue(codeGen);
    codeGen->branchAndStartBlock(endBlock);
}

void LgsIfStmt::generateIfElse(LgsCodeGen* codeGen) const {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    const auto trueBlock = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    const auto elseBlock = codeGen->createBlock(BLOCK_NAME_ELSE);
    const auto endBlock = codeGen->createBlock(BLOCK_NAME_IF_END);
    // if block
    codeGen->builder.CreateCondBr(ifCondIR, trueBlock, elseBlock);
    codeGen->startBlock(trueBlock);
    ifStmtsBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(endBlock);
    // else block
    codeGen->startBlock(elseBlock);
    elseStmtsBlock->createIRValue(codeGen);
    codeGen->branchAndStartBlock(endBlock);
}

void LgsIfStmt::generateComplexIf(LgsCodeGen* codeGen) const {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    auto trueBlock = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    auto elseIfCheckBlock = codeGen->createBlock(BLOCK_NAME_ELSE_IF_CHECK);
    const auto elseBlock = codeGen->createBlock(BLOCK_NAME_ELSE);
    const auto endBlock = codeGen->createBlock(BLOCK_NAME_IF_END);

    // if block
    codeGen->builder.CreateCondBr(ifCondIR, trueBlock, elseIfCheckBlock);
    codeGen->startBlock(trueBlock);
    ifStmtsBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(endBlock);

    for (int i = 0; i < elseIfConds.size(); ++i) {
        codeGen->startBlock(elseIfCheckBlock);
        const auto elseIfCond = elseIfConds[i];
        const auto stmtBlock = elseIfStmtsBlocks[i];
        const auto elseIfCondIR = elseIfCond->getIRValue(codeGen);
        trueBlock = codeGen->createBlock(BLOCK_NAME_ELSE_IF);
        const auto lastIter = i == elseIfConds.size() - 1;
        if (lastIter) {
            if (elseStmtsBlock) {
                codeGen->builder.CreateCondBr(elseIfCondIR, trueBlock, elseBlock);
            } else {
                codeGen->builder.CreateCondBr(elseIfCondIR, trueBlock, endBlock);
            }
        } else {
            elseIfCheckBlock = codeGen->createBlock(BLOCK_NAME_ELSE_IF_CHECK);
            codeGen->builder.CreateCondBr(elseIfCondIR, trueBlock, elseIfCheckBlock);
        }
        codeGen->startBlock(trueBlock);
        stmtBlock->createIRValue(codeGen);
        codeGen->branchIfNeeded(endBlock);
    }

    if (elseStmtsBlock) {
        codeGen->startBlock(elseBlock);
        elseStmtsBlock->createIRValue(codeGen);
        codeGen->branchIfNeeded(endBlock);
    }
    codeGen->startBlock(endBlock);
}

void LgsIfStmt::generatePatternMatching(LgsCodeGen* codeGen) const {
    const auto exprIRValue = ifCond->hashValue(codeGen);
    const auto exitBlock = codeGen->createBlock(BLOCK_NAME_EXIT_PATTERN);
    const auto defaultBlock = codeGen->createBlock(BLOCK_NAME_DEFAULT_CASE);
    const auto switchInst = codeGen->builder.CreateSwitch(exprIRValue, defaultBlock);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        const auto pattern = elseIfConds[i];
        const auto patterIRValue = pattern->hashValue(codeGen);
        const auto IRFunc = codeGen->stack.currentFunc()->getIRFunc(codeGen);
        const auto patternBlock = codeGen->createBlock(BLOCK_NAME_CASE_PREFIX + to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        codeGen->builder.SetInsertPoint(patternBlock);
        elseIfStmtsBlocks[i]->createIRValue(codeGen);
        codeGen->builder.CreateBr(exitBlock);
    }

    codeGen->startBlock(defaultBlock);
    elseStmtsBlock->createIRValue(codeGen);

    codeGen->builder.CreateBr(exitBlock);
    codeGen->startBlock(exitBlock);
}

bool LgsIfStmt::shouldBranch(LgsCodeGen* codeGen, Value* ifCondIR) const {
    if (const auto* constBool = dyn_cast<ConstantInt>(ifCondIR)) {
        if (constBool->isOne()) {
            ifStmtsBlock->createIRValue(codeGen);
        }
        return false;
    }
    return true;
}

LgsIfStmt::~LgsIfStmt() {
    delete ifCond;
    delete ifStmtsBlock;
    for (const auto &elseIfCond : elseIfConds) {
        delete elseIfCond;
    }
    for (const auto &elseIfStmtBlock : elseIfStmtsBlocks) {
        delete elseIfStmtBlock;
    }
    if (elseStmtsBlock) {
        delete elseStmtsBlock;
    }
}