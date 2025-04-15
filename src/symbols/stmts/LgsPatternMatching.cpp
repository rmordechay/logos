#include "stmts/LgsPatternMatching.h"

#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsStr.h"

Value* LgsPatternMatching::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto func = metadata->lgsStack.currentFunc->getIRFunc(metadata);
    const auto exprIRValue = metadata->builder.getInt32(expr->hashValue());
    exitBlock = BasicBlock::Create(context, "exit_pattern_matching");
    defaultCase = BasicBlock::Create(context, "default");
    const auto switchInst = builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = metadata->builder.getInt32(pattern->hashValue());
        const auto patternBlock = BasicBlock::Create(context, "case_" + to_string(i), func);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
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