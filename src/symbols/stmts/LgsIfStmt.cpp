#include "stmts/LgsIfStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsCodeGen.h"

void LgsIfStmt::createIRStmt(LgsCodeGen* codeGen) {
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
}

void LgsIfStmt::generateSimpleIf(LgsCodeGen* codeGen) {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    const auto IRBlockTrue = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockEnd = codeGen->createBlock(BLOCK_NAME_IF_END);
    codeGen->builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockEnd);
    codeGen->startBlock(IRBlockTrue);
    ifBlock->createIRValue(codeGen);
    codeGen->branchAndStartBlock(IRBlockEnd);
}

void LgsIfStmt::generateIfElse(LgsCodeGen* codeGen) {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    const auto IRBlockTrue = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockElse = codeGen->createBlock(BLOCK_NAME_ELSE);
    const auto IRBlockEnd = codeGen->createBlock(BLOCK_NAME_IF_END);
    // if block
    codeGen->builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElse);
    codeGen->startBlock(IRBlockTrue);
    ifBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(IRBlockEnd);
    // else block
    codeGen->startBlock(IRBlockElse);
    elseBlock->createIRValue(codeGen);
    codeGen->branchAndStartBlock(IRBlockEnd);
}

void LgsIfStmt::generateComplexIf(LgsCodeGen* codeGen) {
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(codeGen, ifCondIR)) return;
    auto IRBlockTrue = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    auto IRBlockElseIfCheck = codeGen->createBlock(BLOCK_NAME_ELSE_IF_CHECK);
    const auto IRBlockElse = codeGen->createBlock(BLOCK_NAME_ELSE);
    const auto IRBlockEnd = codeGen->createBlock(BLOCK_NAME_IF_END);

    // if block
    codeGen->builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    codeGen->startBlock(IRBlockTrue);
    ifBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(IRBlockEnd);

    for (int i = 0; i < elseIfs.size(); ++i) {
        const auto elseIfPair = elseIfs[i];
        const auto expr = elseIfPair.first;
        const auto stmtBlock = elseIfPair.second;
        codeGen->startBlock(IRBlockElseIfCheck);
        const auto elseIfCondIR = expr->getIRValue(codeGen);
        IRBlockTrue = codeGen->createBlock(BLOCK_NAME_ELSE_IF);
        const auto lastIter = i == elseIfs.size() - 1;
        if (lastIter) {
            if (IRBlockElse) {
                codeGen->builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElse);
            } else {
                codeGen->builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockEnd);
            }
        } else {
            IRBlockElseIfCheck = codeGen->createBlock(BLOCK_NAME_ELSE_IF_CHECK);
            codeGen->builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElseIfCheck);
        }
        codeGen->startBlock(IRBlockTrue);
        stmtBlock->createIRValue(codeGen);
        codeGen->branchIfNeeded(IRBlockEnd);
    }

    if (IRBlockElse) {
        codeGen->startBlock(IRBlockElse);
        elseBlock->createIRValue(codeGen);
        codeGen->branchIfNeeded(IRBlockEnd);
    }
    codeGen->startBlock(IRBlockEnd);
}

void LgsIfStmt::generatePatternMatching(LgsCodeGen* codeGen) {
    const auto exprIRValue = ifCond->hashValue(codeGen);
    const auto exitBlock = codeGen->createBlock(BLOCK_NAME_EXIT_PATTERN);
    const auto defaultBlock = codeGen->createBlock(BLOCK_NAME_DEFAULT_CASE);
    const auto switchInst = codeGen->builder.CreateSwitch(exprIRValue, defaultBlock);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < elseIfs.size(); ++i) {
        const auto elseIfPair = elseIfs[i];
        const auto expr = elseIfPair.first;
        const auto stmtsBlock = elseIfPair.second;
        const auto patterIRValue = expr->hashValue(codeGen);
        const auto IRFunc = codeGen->stack.currentFunc()->getIRFunc(codeGen);
        const auto patternBlock = codeGen->createBlock(BLOCK_NAME_CASE_PREFIX + to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        codeGen->builder.SetInsertPoint(patternBlock);
        stmtsBlock->createIRValue(codeGen);
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
