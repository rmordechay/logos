#include "loops/LgsForeachLoop.h"

#include "codegen/LgsCodeGen.h"
#include "types/iterables/LgsMap.h"

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

LgsForeachLoop::~LgsForeachLoop() {
    freeExpr(iterExpr);
}
