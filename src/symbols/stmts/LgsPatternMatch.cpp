#include "stmts/LgsPatternMatch.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"

void LgsPatternMatch::createIRStmt(Module* module) {
    const auto func = runtime.stack.currentFunc->getIRFunc(module);
    const auto exprIRValue = builder.getInt32(expr->hashValue(module));
    exitBlock = BasicBlock::Create(context, "exit_pattern_matching");
    defaultCase = BasicBlock::Create(context, "default");
    const auto switchInst = builder.CreateSwitch(exprIRValue, defaultCase);

    vector<BasicBlock*> blocks;
    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto pattern = patterns[i];
        const auto patterIRValue = builder.getInt32(pattern->hashValue(module));
        const auto patternBlock = BasicBlock::Create(context, "case_" + to_string(i), func);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        builder.SetInsertPoint(patternBlock);
        patternsStmtBlocks[i]->createIRValue(module);
        builder.CreateBr(exitBlock);
    }

    startBlock(module, defaultCase);
    elseStmtBlock->createIRValue(module);

    builder.CreateBr(exitBlock);
    startBlock(module, exitBlock);
}

json LgsPatternMatch::asJSON() {
    json tree;
    tree["expr"] = expr->asJSON();
    tree["stmtType"] = "patternMatch";
    return tree;
}
