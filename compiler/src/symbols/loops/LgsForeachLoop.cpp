#include "loops/LgsForeachLoop.h"
#include "types/iterables/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsCgModule& cg) {
    return cg.i32Zero();
}

Value* LgsForeachLoop::loopEnd(LgsCgModule& cg) {
    const auto iter = iterExpr->type->asIterable();
    return cg.builder.CreateTrunc(iter->lenIR(cg, iterExpr->IRValue), cg.i32Ty());
}

void LgsForeachLoop::incAndJumpToCond(LgsCgModule& cg) {
    if (cg.lastInstTerminator()) return;
    iValue = cg.builder.CreateLoad(cg.i32Ty(), iPtr);
    const auto inc = cg.builder.CreateAdd(iValue, cg.i32(1));
    cg.builder.CreateStore(inc, iPtr);
    cg.builder.CreateBr(IRCondBlock);
}

void LgsForeachLoop::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsForeachLoop::~LgsForeachLoop() {
    freeExpr(iterExpr);
}
