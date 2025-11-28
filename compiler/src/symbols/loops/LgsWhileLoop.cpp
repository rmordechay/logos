#include "loops/LgsWhileLoop.h"
#include "exprs/LgsExpr.h"
#include "codegen/LgsCgModule.h"

void LgsWhileLoop::incAndJumpToCond(LgsCgModule& cg) {
    if (cg.lastInstTerminator()) return;
    cg.builder.CreateBr(IRCondBlock);
}

Value* LgsWhileLoop::loopStart(LgsCgModule& cg) {
    assert(0);
}

Value* LgsWhileLoop::loopEnd(LgsCgModule& cg) {
    assert(0);
}

LgsWhileLoop::~LgsWhileLoop() {
    if (condExpr) {
        delete condExpr;
        condExpr = nullptr;
    }
}
