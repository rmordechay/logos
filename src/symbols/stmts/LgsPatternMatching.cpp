#include "stmts/LgsPatternMatching.h"

#include "funcs/LgsFunc.h"

Value* LgsPatternMatching::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto func = metadata->logosStack.currentFunc->getIRFunc(metadata);
    const auto exprIRValue = expr->getIRValue(metadata);
    const auto exitBlock = BasicBlock::Create(context, "exit_pattern_matching");
    const auto defaultCase = BasicBlock::Create(context, "default");
    const auto switchInst = builder.CreateSwitch(exprIRValue, defaultCase);
    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto v = pattern->getIRValue(metadata);
        const auto patternBlock = BasicBlock::Create(context, "case_" + to_string(i), func);
        switchInst->addCase(dyn_cast<ConstantInt>(v), patternBlock);
        builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(metadata);
        builder.CreateBr(exitBlock);
    }
    startBlock(metadata, defaultCase);
    elseStmtBlock->createIRValue(metadata);
    builder.CreateBr(exitBlock);
    startBlock(metadata, exitBlock);
    return nullptr;
}