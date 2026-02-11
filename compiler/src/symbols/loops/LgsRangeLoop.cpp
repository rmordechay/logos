#include "loops/LgsRangeLoop.h"

#include "codegen/LgsCodeGen.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsCodeGen& cg) {
    return cg.toSize(startRange->loadIR(cg));
}

Value* LgsRangeLoop::loopEnd(LgsCodeGen& cg) {
    return cg.toSize(endRange->loadIR(cg));
}

void LgsRangeLoop::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsRangeLoop::~LgsRangeLoop() {
    freeExpr(startRange);
    freeExpr(endRange);
    startRange = nullptr;
    endRange = nullptr;
}
