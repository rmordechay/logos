#include "loops/LgsRangeLoop.h"

#include "codegen/LgsCodeGen.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsCodeGen& cg) {
    return cg.extendToSize(startRange->loadIR(cg));
}

Value* LgsRangeLoop::loopEnd(LgsCodeGen& cg) {
    return cg.extendToSize(endRange->loadIR(cg));
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
