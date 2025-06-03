#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsArray.h"

Value* LgsForeachLoop::loopStart(LgsRuntime* runtime) {
    return i32Zero;
}

Value* LgsForeachLoop::loopEnd(LgsRuntime* runtime) {
    return iterExpr->getLength(runtime);
}

void LgsForeachLoop::setIRIterable(LgsRuntime* runtime) {
    iterPtr = iterExpr->getIRValue(runtime);
}

void LgsForeachLoop::setIRLoopVars(LgsRuntime* runtime) {
    const auto iterType = iterExpr->type->asIterable();
    for (const auto loopVar : loopVars) {
        loopVar->IRValue = iterType->getElement(runtime, iterPtr, iPtr);
    }
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
