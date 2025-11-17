#include "loops/LgsRangeLoop.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

Value* LgsRangeLoop::loopStart(LgsLLVMGen& cg) {
    return startRange->loadIR(cg);
}

Value* LgsRangeLoop::loopEnd(LgsLLVMGen& cg) {
    return endRange->loadIR(cg);
}

LgsRangeLoop* LgsRangeLoop::clone() {
    const auto newLoop = new LgsRangeLoop(*this);
    newLoop->loopVars.clear();
    for (const auto loopVar : loopVars) {
        newLoop->loopVars.push_back(loopVar->clone());
    }
    for (const auto [key, loopVar] : metaVars) {
        newLoop->metaVars[key] = loopVar->clone();
    }
    newLoop->startRange = startRange->clone();
    newLoop->endRange = endRange->clone();
    newLoop->stmtsBlock = stmtsBlock->clone();
    return newLoop;
}

LgsRangeLoop::~LgsRangeLoop() {
    freeExpr(startRange);
    freeExpr(endRange);
    startRange = nullptr;
    endRange = nullptr;
}
