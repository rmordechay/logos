#include "stmts/LgsPatternMatch.h"

#include "configs/LgsDefinitions.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

void LgsPatternMatch::createIRStmt(LgsModule* module) {
    const auto exprIRValue = expr->hashValue(module);
    exitBlock = BasicBlock::Create(module->context, BLOCK_NAME_EXIT_PATTERN);
    defaultCase = BasicBlock::Create(module->context, BLOCK_NAME_DEFAULT_CASE);
    const auto switchInst = module->builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = pattern->hashValue(module);
        const auto IRFunc = module->stack.currentFunc()->getIRFunc(module);
        const auto patternBlock = BasicBlock::Create(module->context, BLOCK_NAME_CASE_PREFIX + to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        module->builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(module);
        module->builder.CreateBr(exitBlock);
    }

    startBlock(module, defaultCase);
    elseStmtBlock->createIRValue(module);

    module->builder.CreateBr(exitBlock);
    startBlock(module, exitBlock);
}
