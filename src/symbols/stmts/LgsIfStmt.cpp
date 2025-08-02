#include "stmts/LgsIfStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsCodeGen.h"

void LgsIfStmt::createIRStmt(LgsCodeGen* codeGen) {
    if (isPatternMatching) {
        return generatePatternMatching(codeGen);
    }
    codeGen->stack.enterScope(this, ifBlock);
    const auto ifCondIR = ifCond->getIRValue(codeGen);
    if (!shouldBranch(ifCondIR)) {
        ifBlock->createIRValue(codeGen);
        codeGen->stack.exitScope();
    } else if (elseIfs.empty()) {
        if (!elseBlock) {
            generateSimpleIf(codeGen, ifCondIR);
            codeGen->stack.exitScope();
        } else {
            generateIfWithElse(codeGen, ifCondIR);
        }
    } else {
        generateElseIf(codeGen, ifCondIR);
    }
}

void LgsIfStmt::generateSimpleIf(LgsCodeGen* codeGen, Value* ifCondIR) const {
    const auto IRBlockIfTrue = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockIfFalse = codeGen->createBlock(BLOCK_NAME_IF_FALSE);
    codeGen->builder.CreateCondBr(ifCondIR, IRBlockIfTrue, IRBlockIfFalse);
    codeGen->startBlock(IRBlockIfTrue);
    ifBlock->createIRValue(codeGen);
    codeGen->branchAndStartBlock(IRBlockIfFalse);
}

void LgsIfStmt::generateIfWithElse(LgsCodeGen* codeGen, Value* ifCondIR) {
    const auto IRBlockTrue = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockElse = codeGen->createBlock(BLOCK_NAME_ELSE);
    const auto IRBlockEnd = codeGen->createBlock(BLOCK_NAME_IF_FALSE);

    // if block (caller entered the scope)
    codeGen->builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElse);
    codeGen->startBlock(IRBlockTrue);
    ifBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(IRBlockEnd);
    codeGen->stack.exitScope();

    // else block
    codeGen->stack.enterScope(this, elseBlock);
    codeGen->startBlock(IRBlockElse);
    elseBlock->createIRValue(codeGen);
    codeGen->branchAndStartBlock(IRBlockEnd);
    codeGen->stack.exitScope();
}

void LgsIfStmt::generateElseIf(LgsCodeGen* codeGen, Value* ifCondIR) {
    auto IRBlockTrue = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    auto IRBlockElseIfCheck = codeGen->createBlock(BLOCK_NAME_ELSE_IF_CHECK);
    const auto IRBlockElse = codeGen->createBlock(BLOCK_NAME_ELSE);
    const auto IRBlockEnd = codeGen->createBlock(BLOCK_NAME_IF_FALSE);

    // if block (caller entered the scope)
    codeGen->builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    codeGen->startBlock(IRBlockTrue);
    ifBlock->createIRValue(codeGen);
    codeGen->branchIfNeeded(IRBlockEnd);
    codeGen->stack.exitScope();

    for (int i = 0; i < elseIfs.size(); ++i) {
        const auto elseIfPair = elseIfs[i];
        const auto expr = elseIfPair.first;
        const auto stmtBlock = elseIfPair.second;
        codeGen->stack.enterScope(this, stmtBlock);
        codeGen->startBlock(IRBlockElseIfCheck);
        const auto elseIfCondIR = expr->getIRValue(codeGen);
        IRBlockTrue = codeGen->createBlock(BLOCK_NAME_ELSE_IF);
        if (i == elseIfs.size() - 1) {
            if (elseBlock) {
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
        codeGen->stack.exitScope();
    }

    if (elseBlock) {
        codeGen->stack.enterScope(this, elseBlock);
        codeGen->startBlock(IRBlockElse);
        elseBlock->createIRValue(codeGen);
        codeGen->branchIfNeeded(IRBlockEnd);
        codeGen->stack.exitScope();
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
        codeGen->stack.enterScope(this, stmtsBlock);
        const auto patterIRValue = expr->hashValue(codeGen);
        const auto IRFunc = codeGen->stack.currentFunc()->getIRFunc(codeGen);
        const auto patternBlock = codeGen->createBlock(BLOCK_NAME_CASE_PREFIX + to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        codeGen->builder.SetInsertPoint(patternBlock);
        stmtsBlock->createIRValue(codeGen);
        codeGen->builder.CreateBr(exitBlock);
        codeGen->stack.exitScope();
    }

    if (elseBlock) {
        codeGen->stack.enterScope(this, elseBlock);
        codeGen->startBlock(defaultBlock);
        elseBlock->createIRValue(codeGen);
        codeGen->stack.exitScope();
    }

    codeGen->builder.CreateBr(exitBlock);
    codeGen->startBlock(exitBlock);
}

bool LgsIfStmt::shouldBranch(Value* ifCondIR) {
    if (const auto* constBool = dyn_cast<ConstantInt>(ifCondIR)) {
        return constBool->isOne();
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
