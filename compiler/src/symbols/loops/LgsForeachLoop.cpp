#include "loops/LgsForeachLoop.h"
#include "types/iterables/LgsMap.h"
#include "LgsUtils.h"

Value* LgsForeachLoop::loopStart(LgsLLVMGen& cg) {
    return cg.i32Zero();
}

Value* LgsForeachLoop::loopEnd(LgsLLVMGen& cg) {
    const auto iter = iterExpr->type->asIterable();
    return cg.builder.CreateTrunc(iter->lengthIR(cg, iterExpr->IRValue), cg.i32Ty());
}

void LgsForeachLoop::incAndJumpToCond(LgsLLVMGen& cg) {
    if (cg.lastInstTerminator()) return;
    iValue = cg.builder.CreateLoad(cg.i32Ty(), iPtr);
    const auto inc = cg.builder.CreateAdd(iValue, cg.i32(1));
    cg.builder.CreateStore(inc, iPtr);
    cg.builder.CreateBr(IRCondBlock);
}

LgsForeachLoop::~LgsForeachLoop() {
    freeExpr(iterExpr);
}
