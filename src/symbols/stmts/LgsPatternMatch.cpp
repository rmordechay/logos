#include "stmts/LgsPatternMatch.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

void LgsPatternMatch::createIRStmt(LgsModule* runtime) {
    const auto exprIRValue = expr->hashValue(runtime);
    exitBlock = BasicBlock::Create(runtime->context, "exit_pattern_matching");
    defaultCase = BasicBlock::Create(runtime->context, "default");
    const auto switchInst = runtime->builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = pattern->hashValue(runtime);
        const auto patternBlock = BasicBlock::Create(runtime->context, "case_" + to_string(i), runtime->IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        runtime->builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(runtime);
        runtime->builder.CreateBr(exitBlock);
    }

    startBlock(runtime, defaultCase);
    elseStmtBlock->createIRValue(runtime);

    runtime->builder.CreateBr(exitBlock);
    startBlock(runtime, exitBlock);
}