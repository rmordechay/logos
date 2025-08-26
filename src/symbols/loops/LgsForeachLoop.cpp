#include "loops/LgsForeachLoop.h"
#include "types/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsLLVM& codeGen) {
    return codeGen.sizeZero();
}

Value* LgsForeachLoop::loopEnd(LgsLLVM& codeGen) {
    return iterExpr->type->asIterable()->IRLength(codeGen, iterExpr);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
}
