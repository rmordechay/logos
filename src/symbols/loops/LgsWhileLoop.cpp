#include "loops/LgsWhileLoop.h"
#include "exprs/LgsExpr.h"
#include "codegen/LgsLLVM.h"

void LgsWhileLoop::incAndJumpToCond(LgsLLVM& codeGen) {
    if (codeGen.lastInstTerminator()) return;
    codeGen.builder.CreateBr(IRCondBlock);
}

Value* LgsWhileLoop::loopStart(LgsLLVM& codeGen) {
    assert(0);
}

Value* LgsWhileLoop::loopEnd(LgsLLVM& codeGen) {
    assert(0);
}

LgsWhileLoop::~LgsWhileLoop() {
    if (condExpr) {
        delete condExpr;
        condExpr = nullptr;
    }
}
