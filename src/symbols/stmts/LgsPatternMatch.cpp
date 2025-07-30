#include "stmts/LgsPatternMatch.h"

#include "configs/LgsDefinitions.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

#include "utils/LgsUtils.h"

void LgsPatternMatch::createIRStmt(LgsCodeGen* codeGen) {
    const auto exprIRValue = expr->hashValue(codeGen);
    exitBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_EXIT_PATTERN);
    defaultCase = BasicBlock::Create(codeGen->context, BLOCK_NAME_DEFAULT_CASE);
    const auto switchInst = codeGen->builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = pattern->hashValue(codeGen);
        const auto IRFunc = codeGen->stack.currentFunc()->getIRFunc(codeGen);
        const auto patternBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_CASE_PREFIX + to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        codeGen->builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(codeGen);
        codeGen->builder.CreateBr(exitBlock);
    }

    codeGen->startBlock(defaultCase);
    elseStmtBlock->createIRValue(codeGen);

    codeGen->builder.CreateBr(exitBlock);
    codeGen->startBlock(exitBlock);
}
