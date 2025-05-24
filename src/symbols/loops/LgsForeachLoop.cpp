#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "types/array/LgsArray.h"

Value* LgsForeachLoop::loopStart(CodeGenMetadata* metadata) {
    return i32Zero;
}

Value* LgsForeachLoop::loopEnd(CodeGenMetadata* metadata) {
    return iterExpr->getLength(metadata);
}

void LgsForeachLoop::setIRIterable(CodeGenMetadata* metadata) {
    // const auto iterValue = iterExpr->getIRValue(metadata);
    // const auto iterType = iterExpr->type->asIterable();
    iterPtr = iterExpr->getIRValue(metadata);
    // metadata->builder.CreateStore(iterValue, iterPtr);
}

void LgsForeachLoop::setIRLoopVars(CodeGenMetadata* metadata) {
    assert(iterExpr);
    const auto iterType = iterExpr->type->asIterable();
    for (const auto loopVar : loopVars) {
        loopVar->IRValue = iterType->getElement(metadata, iterPtr, iPtr);
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
