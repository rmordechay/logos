#include "loops/LgsWhileLoop.h"

#include "exprs/LgsExpr.h"
#include "codegen/LgsCodeGen.h"
#include "stmts/LgsStmtsBlock.h"

void LgsWhileLoop::incAndJumpToCond(LgsCodeGen& codeGen) const {
    if (codeGen.lastInstTerminator()) return;
    codeGen.builder.CreateBr(IRCondBlock);
}

LgsWhileLoop::~LgsWhileLoop() {
    if (condExpr) {
        delete condExpr;
        condExpr = nullptr;
    }
}
