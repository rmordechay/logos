#include "loops/LgsWhileLoop.h"
#include "exprs/LgsExpr.h"
#include "codegen/LgsCodeGen.h"

void LgsWhileLoop::incAndJumpToCond(LgsCodeGen& cg) {
    if (cg.lastInstTerminator()) return;
    cg.builder.CreateBr(IRCondBlock);
}

Value* LgsWhileLoop::loopStart(LgsCodeGen& cg) {
    assert(0);
}

Value* LgsWhileLoop::loopEnd(LgsCodeGen& cg) {
    assert(0);
}

void LgsWhileLoop::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsWhileLoop::~LgsWhileLoop() {
    if (condExpr) {
        delete condExpr;
        condExpr = nullptr;
    }
}
