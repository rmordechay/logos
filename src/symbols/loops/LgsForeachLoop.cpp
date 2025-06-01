#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsStmtBlock.h"
#include "types/array/LgsArray.h"

Value* LgsForeachLoop::loopStart(CodegenMetadata* metadata) {
    return i32Zero;
}

Value* LgsForeachLoop::loopEnd(CodegenMetadata* metadata) {
    return iterExpr->getLength(metadata);
}

void LgsForeachLoop::setIRIterable(CodegenMetadata* metadata) {
    iterPtr = iterExpr->getIRValue(metadata);
}

void LgsForeachLoop::setIRLoopVars(CodegenMetadata* metadata) {
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
