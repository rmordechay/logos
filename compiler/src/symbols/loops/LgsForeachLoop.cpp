#include "loops/LgsForeachLoop.h"

#include <assert.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <unordered_map>
#include <vector>

#include "codegen/LgsCodeGen.h"
#include "stmts/LgsVarDec.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "loops/LgsMetaVar.h"
#include "stmts/LgsStmt.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/iterables/LgsIterable.h"

Value* LgsForeachLoop::loopStart(LgsCodeGen& cg) {
    return cg.zeroSize();
}

Value* LgsForeachLoop::loopEnd(LgsCodeGen& cg) {
    const auto iter = iterExpr->type->asIterable();
    return iter->lenIR(cg, iterExpr->IRValue);
}

void LgsForeachLoop::incAndJumpToCond(LgsCodeGen& cg) {
    if (cg.lastInstTerminator()) return;
    const auto inc = cg.builder.CreateAdd(loadIndex(cg), cg.usize(1));
    cg.store(inc, iPtr);
    cg.builder.CreateBr(IRCondBlock);
}

void LgsForeachLoop::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsStmt* LgsForeachLoop::clone() {
    const auto newLgsRangeLoop = new LgsForeachLoop(*this);
    if (iterExpr) newLgsRangeLoop->iterExpr = iterExpr->clone();
    if (stmtsBlock) newLgsRangeLoop->stmtsBlock = stmtsBlock->clone();
    loopVars.clear();
    for (const auto var : loopVars) {
        newLgsRangeLoop->loopVars.push_back(var->clone()->asVarDec());
    }
    metaVars.clear();
    for (const auto var : metaVars) {
        newLgsRangeLoop->metaVars[var.first] = var.second->clone()->asMetaVar();
    }
    return newLgsRangeLoop;
}

LgsForeachLoop::~LgsForeachLoop() {
    freeExpr(iterExpr);
}
