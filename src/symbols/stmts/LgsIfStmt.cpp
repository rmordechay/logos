#include "stmts/LgsIfStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsCodeGen.h"

void LgsIfStmt::createIRValue(LgsCodeGen* codeGen) {
    if (isPatternMatching) {
        generatePatternMatching(codeGen);
    } else if (elseIfs.empty()) {
        if (!elseBlock) {
            generateSimpleIf(codeGen);
        } else {
            generateIfWithElse(codeGen);
        }
    } else {
        generateElseIf(codeGen);
    }
}

void LgsIfStmt::generateSimpleIf(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, ifBlock);
    generateSimpleIf(codeGen, ifCond, [this, codeGen] {
        ifBlock->createIRValue(codeGen);
    });
    codeGen->stack.exitScope();
}

void LgsIfStmt::generateIfWithElse(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, ifBlock);
    const auto ifCondIR = ifCond->getIRValue(codeGen);
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

void LgsIfStmt::generateElseIf(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, ifBlock);
    const auto ifCondIR = ifCond->getIRValue(codeGen);
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
        const auto [expr, stmtBlock] = elseIfs[i];
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
    const auto defaultBlock = codeGen->createBlock(BLOCK_NAME_DEFAULT_CASE);
    const auto exitBlock = codeGen->createBlock(BLOCK_NAME_EXIT_PATTERN);

    const auto exprIRValue = ifCond->hash(codeGen);
    SwitchInst* switchInst;
    if (elseBlock) {
        const auto numOfCases = elseIfs.size() + !!elseBlock;
        switchInst = codeGen->builder.CreateSwitch(exprIRValue, defaultBlock, numOfCases);
    } else {
        switchInst = codeGen->builder.CreateSwitch(exprIRValue, exitBlock, elseIfs.size());
    }

    std::vector<BasicBlock*> blocks;
    for (size_t i = 0; i < elseIfs.size(); ++i) {
        const auto [expr, stmtsBlock] = elseIfs[i];
        codeGen->stack.enterScope(this, stmtsBlock);
        const auto patterIRValue = expr->hash(codeGen);
        const auto IRFunc = codeGen->stack.currentFunc()->getIRFunc(codeGen);
        const auto patternBlock = codeGen->createBlock(BLOCK_NAME_CASE_PREFIX + std::to_string(i), IRFunc);
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
        codeGen->builder.CreateBr(exitBlock);
        codeGen->stack.exitScope();
    }

    codeGen->startBlock(exitBlock);
}

json::value LgsIfStmt::asJSON() {
    assert(0);
}

void LgsIfStmt::generateSimpleIf(LgsCodeGen* codeGen, LgsExpr* cond, const std::function<void()>& trueBlockCb) {
    const auto ifCondIR = cond->getIRValue(codeGen);
    const auto IRBlockIfTrue = codeGen->createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockIfFalse = codeGen->createBlock(BLOCK_NAME_IF_FALSE);
    codeGen->builder.CreateCondBr(ifCondIR, IRBlockIfTrue, IRBlockIfFalse);
    codeGen->startBlock(IRBlockIfTrue);
    trueBlockCb();
    codeGen->branchAndStartBlock(IRBlockIfFalse);
}

LgsIfStmt::~LgsIfStmt() {
    if (ifCond) {
        delete ifCond;
        ifCond = nullptr;
    }
    if (ifBlock) {
        delete ifBlock;
        ifBlock = nullptr;
    }
    if (elseBlock) {
        delete elseBlock;
        elseBlock = nullptr;
    }
    for (const auto& [expr, block] : elseIfs) {
        delete expr;
        delete block;
    }
    elseIfs.clear();
}
