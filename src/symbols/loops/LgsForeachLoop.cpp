#include "loops/LgsForeachLoop.h"
#include "types/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsLLVMGen& cg) {
    return cg.sizeZero();
}

Value* LgsForeachLoop::loopEnd(LgsLLVMGen& cg) {
    return iterExpr->type->asIterable()->IRLength(cg, iterExpr);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
}
