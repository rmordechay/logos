#include "loops/LgsRangeLoop.h"

#include "codegen/LgsCgModule.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsCgModule& cg) {
    return cg.extendToSize(startRange->loadIR(cg));
}

Value* LgsRangeLoop::loopEnd(LgsCgModule& cg) {
    return cg.extendToSize(endRange->loadIR(cg));
}

void LgsRangeLoop::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsRangeLoop::~LgsRangeLoop() {
    freeExpr(startRange);
    freeExpr(endRange);
    startRange = nullptr;
    endRange = nullptr;
}
