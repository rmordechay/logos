#include "stmts/LgsPatternMatch.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

void LgsPatternMatch::createIRStmt(LgsModule* module) {
    const auto exprIRValue = expr->hashValue(module);
    exitBlock = BasicBlock::Create(module->context, "exit_pattern_matching");
    defaultCase = BasicBlock::Create(module->context, "default");
    const auto switchInst = module->builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = pattern->hashValue(module);
        const auto IRFunc = module->stack.currentFunc->getIRFunc(module);
        const auto patternBlock = BasicBlock::Create(module->context, "case_" + to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        module->builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(module);
    }

    elseStmtBlock->createIRValue(module);

}
