#include "stmts/LgsIfStmt.h"

#include "codegen/CodegenMetadata.h"
#include "logos/LgsGlobals.h"

void LgsIfStmt::createIRStmt(Module* module) {
    runtime.enterScope();
    if (elseBlock || elseIfConds.size() > 0) {
        computeComplexIf(module);
    } else {
        computeSimpleIf(module);
    }
    runtime.exitScope();
}


void LgsIfStmt::computeSimpleIf(Module* module) {

    ifTrueBlock = createBasicBlock(BB_IF_TRUE);
    ifEndBlock = createBasicBlock(BB_IF_END);
    elseBlock = createBasicBlock(BB_ELSE);

    // if block
    const auto ifCondIR = ifCond->getIRValue(module);
    if (!elseStmtBlock) {
        builder.CreateCondBr(ifCondIR, ifTrueBlock, ifEndBlock);
    } else {
        builder.CreateCondBr(ifCondIR, ifTrueBlock, elseBlock);
    }
    startBlock(module, ifTrueBlock);
    ifStmtBlock->createIRValue(module);
    if (builder.GetInsertBlock()->getTerminator()) return;
    builder.CreateBr(ifEndBlock);

    // else block
    createElseBlock(module, elseBlock, ifEndBlock);

    // exit
    startBlock(module, ifEndBlock);
}

void LgsIfStmt::computeComplexIf(Module* module) {

    ifTrueBlock = createBasicBlock(BB_IF_TRUE);
    elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK);
    ifEndBlock = createBasicBlock(BB_IF_END);
    elseBlock = createBasicBlock(BB_ELSE);

    // if block
    const auto ifCondIR = ifCond->getIRValue(module);
    builder.CreateCondBr(ifCondIR, ifTrueBlock, elseIfCheckBlock);
    startBlock(module, ifTrueBlock);
    ifStmtBlock->createIRValue(module);
    builder.CreateBr(ifEndBlock);

    // else if blocks
    createElseIfBlocks(module);

    // else block
    createElseBlock(module, elseBlock, ifEndBlock);

    // exit
    if (!builder.GetInsertBlock()->getTerminator()) {
        startBlock(module, ifEndBlock);
    }
}

void LgsIfStmt::createElseIfBlocks(Module* module) {

    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        startBlock(module, elseIfCheckBlock);
        const auto elseIfCondIR = elseIfConds[i]->getIRValue(module);
        const auto elseIfStartBlock = createBasicBlock(BB_ELSE_IF_START);
        const auto lastIteration = elseIfConds.size() - 1;
        if (i == lastIteration) {
            if (elseStmtBlock) {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseBlock);
            } else {
                builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, ifEndBlock);
            }
        } else {
            elseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK);
            builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, elseIfCheckBlock);
        }

        startBlock(module, elseIfStartBlock);
        elseIfStmtBlocks[i]->createIRValue(module);
        builder.CreateBr(ifEndBlock);
    }
}

void LgsIfStmt::createElseBlock(Module* module, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const {
    if (!elseStmtBlock) return;
    startBlock(module, elseBlock);
    elseStmtBlock->createIRValue(module);
    builder.CreateBr(ifEndBlock);
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
