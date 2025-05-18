#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsStrConst.h"

Value* LgsForeachLoop::loopStart(CodeGenMetadata* metadata) {
    return i32Zero;
}

Value* LgsForeachLoop::loopEnd(CodeGenMetadata* metadata) {
    return iterExpr->getLength(metadata);
}

void LgsForeachLoop::setIRLoopVars(CodeGenMetadata* metadata) {
    assert(iterExpr);
    for (const auto loopVar : loopVars) {
        // loopVar->setIRValue(iValue);
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
