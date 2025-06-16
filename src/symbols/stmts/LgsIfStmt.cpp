#include "stmts/LgsIfStmt.h"
#include "logos/LgsRuntime.h"

void LgsIfStmt::createIRStmt(LgsRuntime* runtime) {
    runtime->stack.enterScope(IF_SCOPE, this);
    if (!elseStmtBlock && elseIfConds.empty()) {
        computeSimpleIf(runtime);
    }
    runtime->stack.exitScope(IF_SCOPE);
}

void LgsIfStmt::computeSimpleIf(LgsRuntime* runtime) {
    IRIfTrueBlock = createBasicBlock(BB_IF_TRUE, context);
    IRIfEndBlock = createBasicBlock(BB_IF_END, context);
    IRElseBlock = createBasicBlock(BB_ELSE, context);

    // if block
    const auto ifCondIR = ifCond->getIRValue(runtime);
    runtime->builder.CreateCondBr(ifCondIR, IRIfTrueBlock, IRIfEndBlock);
    startBlock(runtime, IRIfTrueBlock);
    ifStmtBlock->createIRValue(runtime);
    if (!runtime->builder.GetInsertBlock()->getTerminator()) {
        runtime->builder.CreateBr(IRIfEndBlock);
    }
    // exit
    startBlock(runtime, IRIfEndBlock);
}

void LgsIfStmt::computeComplexIf(LgsRuntime* runtime) {

}

void LgsIfStmt::createElseIfBlocks(LgsRuntime* runtime) {
    auto& ctx = runtime->module->getContext();
    for (size_t i = 0; i < elseIfConds.size(); ++i) {
        startBlock(runtime, IRElseIfCheckBlock);
        const auto elseIfCondIR = elseIfConds[i]->getIRValue(runtime);
        const auto elseIfStartBlock = createBasicBlock(BB_ELSE_IF_START, ctx);
        const auto lastIteration = elseIfConds.size() - 1;
        if (i == lastIteration) {
            if (elseStmtBlock) {
                runtime->builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, IRElseBlock);
            } else {
                runtime->builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, IRIfEndBlock);
            }
        } else {
            IRElseIfCheckBlock = createBasicBlock(BB_ELSE_IF_CHECK, ctx);
            runtime->builder.CreateCondBr(elseIfCondIR, elseIfStartBlock, IRElseIfCheckBlock);
        }

        startBlock(runtime, elseIfStartBlock);
        elseIfStmtBlocks[i]->createIRValue(runtime);
        runtime->builder.CreateBr(IRIfEndBlock);
    }
}

void LgsIfStmt::createElseBlock(LgsRuntime* runtime, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const {
    if (!elseStmtBlock) return;
    startBlock(runtime, elseBlock);
    elseStmtBlock->createIRValue(runtime);
    runtime->builder.CreateBr(ifEndBlock);
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
