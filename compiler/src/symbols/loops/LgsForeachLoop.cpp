#include "loops/LgsForeachLoop.h"
#include "types/iterables/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsCgModule& cg) {
    return cg.sizeZero();
}

Value* LgsForeachLoop::loopEnd(LgsCgModule& cg) {
    const auto iter = iterExpr->type->asIterable();
    return iter->lenIR(cg, iterExpr->IRValue);
}

void LgsForeachLoop::incAndJumpToCond(LgsCgModule& cg) {
    if (cg.lastInstTerminator()) return;
    const auto inc = cg.builder.CreateAdd(loadIndex(cg), cg.usize(1));
    cg.store(inc, iPtr);
    cg.builder.CreateBr(IRCondBlock);
}

void LgsForeachLoop::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsForeachLoop::~LgsForeachLoop() {
    freeExpr(iterExpr);
}
