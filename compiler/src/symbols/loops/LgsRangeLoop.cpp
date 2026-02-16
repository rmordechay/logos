#include "loops/LgsRangeLoop.h"

#include "codegen/LgsCodeGen.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsCodeGen& cg) {
    return cg.toSize(startRange->IRValue);
}

Value* LgsRangeLoop::loopEnd(LgsCodeGen& cg) {
    return cg.toSize(endRange->IRValue);
}

void LgsRangeLoop::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsStmt* LgsRangeLoop::clone() {
    const auto newLgsRangeLoop = new LgsRangeLoop(*this);
    if (startRange) newLgsRangeLoop->startRange = startRange->clone();
    if (endRange) newLgsRangeLoop->endRange = endRange->clone();
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

LgsRangeLoop::~LgsRangeLoop() {
    freeExpr(startRange);
    freeExpr(endRange);
    startRange = nullptr;
    endRange = nullptr;
}
