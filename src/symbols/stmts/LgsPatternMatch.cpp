#include "stmts/LgsPatternMatch.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"

void LgsPatternMatch::createIRStmt(LgsRuntime* runtime) {
    const auto func = runtime->stack.currentFunc->getIRFunc(runtime);
    const auto exprIRValue = runtime->builder.getInt32(expr->hashValue(runtime));
    exitBlock = BasicBlock::Create(context, "exit_pattern_matching");
    defaultCase = BasicBlock::Create(context, "default");
    const auto switchInst = runtime->builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = runtime->builder.getInt32(pattern->hashValue(runtime));
        const auto patternBlock = BasicBlock::Create(context, "case_" + to_string(i), func);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        runtime->builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(runtime);
        runtime->builder.CreateBr(exitBlock);
    }

    startBlock(runtime, defaultCase, nullptr);
    elseStmtBlock->createIRValue(runtime);

    runtime->builder.CreateBr(exitBlock);
    startBlock(runtime, exitBlock, nullptr);
}

json LgsPatternMatch::asJSON() {
    json tree;
    tree["expr"] = expr->asJSON();
    tree["stmtType"] = "patternMatch";
    return tree;
}
