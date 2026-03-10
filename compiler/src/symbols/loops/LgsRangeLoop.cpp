#include "loops/LgsRangeLoop.h"

#include <assert.h>
#include <unordered_map>
#include <vector>

#include "codegen/LgsCodeGen.h"
#include "stmts/LgsVarDec.h"
#include "exprs/LgsExpr.h"
#include "loops/LgsMetaVar.h"
#include "stmts/LgsStmt.h"
#include "stmts/LgsStmtsBlock.h"

Value* LgsRangeLoop::loopStart(LgsCodeGen& cg) {
    return cg.toSize(startRange->IRValue);
}

Value* LgsRangeLoop::loopEnd(LgsCodeGen& cg) {
    return cg.toSize(endRange->IRValue);
}

void LgsRangeLoop::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsStmt* LgsRangeLoop::clone() const {
    const auto newLgsRangeLoop = new LgsRangeLoop(*this);
    if (startRange) newLgsRangeLoop->startRange = startRange->clone();
    if (endRange) newLgsRangeLoop->endRange = endRange->clone();
    if (stmtsBlock) newLgsRangeLoop->stmtsBlock = stmtsBlock->clone();
    newLgsRangeLoop->loopVars.clear();
    for (const auto var : loopVars) {
        newLgsRangeLoop->loopVars.push_back(var->clone()->asVarDec());
    }
    newLgsRangeLoop->metaVars.clear();
    for (const auto var : metaVars) {
        newLgsRangeLoop->metaVars[var.first] = var.second->clone()->asMetaVar();
    }
    return newLgsRangeLoop;
}

LgsRangeLoop::~LgsRangeLoop() {
    freeExpr(startRange);
    freeExpr(endRange);
    startRange = nullptr;
    endRange = nullptr;
}
