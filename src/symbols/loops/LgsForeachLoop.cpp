#include "loops/LgsForeachLoop.h"
#include "types/iterables/LgsMap.h"
#include "utils/LgsUtils.h"

Value* LgsForeachLoop::loopStart(LgsLLVMGen& cg) {
    return cg.sizeZero();
}

Value* LgsForeachLoop::loopEnd(LgsLLVMGen& cg) {
    return iterExpr->type->asIterable()->lengthIR(cg, iterExpr->IRValue);
}

LgsForeachLoop::~LgsForeachLoop() {
    freeExpr(iterExpr);
}
