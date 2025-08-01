#include "stmts/LgsIfStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsCodeGen.h"

void LgsIfStmt::createIRStmt(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(IF_SCOPE, this);
    if (isPatternMatching) {
        generatePatternMatching(codeGen);
    } else {
        if (elseIfs.empty()) {
            if (!elseBlock) {
                generateSimpleIf(codeGen);
            } else {
                generateIfElse(codeGen);
            }
        } else {
            generateComplexIf(codeGen);
        }
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
    ifBlock->createIRValue(codeGen);
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
    ifBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(endBlock);
    // else block
    codeGen->startBlock(elseBlock);
    elseBlock->createIRValue(codeGen);
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
    ifBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(endBlock);

    for (int i = 0; i < elseIfs.size(); ++i) {
        codeGen->startBlock(elseIfCheckBlock);
        const auto elseIfPair = elseIfs[i];
        const auto expr = elseIfPair.first;
        const auto stmtBlock = elseIfPair.second;
        const auto elseIfCondIR = expr->getIRValue(codeGen);
        trueBlock = codeGen->createBlock(BLOCK_NAME_ELSE_IF);
        const auto lastIter = i == elseIfs.size() - 1;
        if (lastIter) {
            if (elseBlock) {
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

    if (elseBlock) {
        codeGen->startBlock(elseBlock);
        elseBlock->createIRValue(codeGen);
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
    for (size_t i = 0; i < elseIfs.size(); ++i) {
        const auto elseIfPair = elseIfs[i];
        const auto patterIRValue = elseIfPair.first->hashValue(codeGen);
        const auto IRFunc = codeGen->stack.currentFunc()->getIRFunc(codeGen);
        const auto patternBlock = codeGen->createBlock(BLOCK_NAME_CASE_PREFIX + to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        codeGen->builder.SetInsertPoint(patternBlock);
        elseIfs[i].second->createIRValue(codeGen);
        codeGen->builder.CreateBr(exitBlock);
    }

    codeGen->startBlock(defaultBlock);
    elseBlock->createIRValue(codeGen);

    codeGen->builder.CreateBr(exitBlock);
    codeGen->startBlock(exitBlock);
}

bool LgsIfStmt::shouldBranch(LgsCodeGen* codeGen, Value* ifCondIR) const {
    if (const auto* constBool = dyn_cast<ConstantInt>(ifCondIR)) {
        if (constBool->isOne()) {
            ifBlock->createIRValue(codeGen);
        }
        return false;
    }
    return true;
}

LgsIfStmt::~LgsIfStmt() {
    delete ifCond;
    delete ifBlock;
    for (const auto &elseIfStmtBlock : elseIfs) {
        delete elseIfStmtBlock.first;
        delete elseIfStmtBlock.second;
    }
    if (elseBlock) {
        delete elseBlock;
    }
}