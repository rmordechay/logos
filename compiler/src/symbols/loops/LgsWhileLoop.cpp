#include "loops/LgsWhileLoop.h"
#include "exprs/LgsExpr.h"
#include "codegen/LgsLLVMGen.h"

void LgsWhileLoop::incAndJumpToCond(LgsLLVMGen& cg) {
    if (cg.lastInstTerminator()) return;
    cg.builder.CreateBr(IRCondBlock);
}

Value* LgsWhileLoop::loopStart(LgsLLVMGen& cg) {
    assert(0);
}

Value* LgsWhileLoop::loopEnd(LgsLLVMGen& cg) {
    assert(0);
}

LgsWhileLoop::~LgsWhileLoop() {
    if (condExpr) {
        delete condExpr;
        condExpr = nullptr;
    }
}
