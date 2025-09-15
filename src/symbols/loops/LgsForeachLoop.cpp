#include "loops/LgsForeachLoop.h"
#include "types/iterables/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsLLVMGen& cg) {
    return cg.sizeZero();
}

Value* LgsForeachLoop::loopEnd(LgsLLVMGen& cg) {
    return iterExpr->type->asIterable()->IRLength(cg, iterExpr->IRValue);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
}
