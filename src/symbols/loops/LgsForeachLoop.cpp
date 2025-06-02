#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsArray.h"

Value* LgsForeachLoop::loopStart(Module* module) {
    return i32Zero;
}

Value* LgsForeachLoop::loopEnd(Module* module) {
    return iterExpr->getLength(module);
}

void LgsForeachLoop::setIRIterable(Module* module) {
    iterPtr = iterExpr->getIRValue(module);
}

void LgsForeachLoop::setIRLoopVars(Module* module) {
    const auto iterType = iterExpr->type->asIterable();
    for (const auto loopVar : loopVars) {
        loopVar->IRValue = iterType->getElement(module, iterPtr, iPtr);
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
