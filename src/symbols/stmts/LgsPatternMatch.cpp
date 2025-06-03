#include "stmts/LgsPatternMatch.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"

void LgsPatternMatch::createIRStmt(LgsRuntime* runtime) {
    const auto func = runtime->stack.currentFunc->getIRFunc(runtime);
    const auto exprIRValue = builder.getInt32(expr->hashValue(runtime));
    exitBlock = BasicBlock::Create(context, "exit_pattern_matching");
    defaultCase = BasicBlock::Create(context, "default");
    const auto switchInst = builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = builder.getInt32(pattern->hashValue(runtime));
        const auto patternBlock = BasicBlock::Create(context, "case_" + to_string(i), func);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(runtime);
        builder.CreateBr(exitBlock);
    }

    startBlock(defaultCase, nullptr);
    elseStmtBlock->createIRValue(runtime);

    builder.CreateBr(exitBlock);
    startBlock(exitBlock, nullptr);
}

json LgsPatternMatch::asJSON() {
    json tree;
    tree["expr"] = expr->asJSON();
    tree["stmtType"] = "patternMatch";
    return tree;
}
