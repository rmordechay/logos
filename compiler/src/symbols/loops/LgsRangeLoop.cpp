#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsCgModule& cg) {
    return startRange->loadIR(cg);
}

Value* LgsRangeLoop::loopEnd(LgsCgModule& cg) {
    return endRange->loadIR(cg);
}

LgsRangeLoop::~LgsRangeLoop() {
    freeExpr(startRange);
    freeExpr(endRange);
    startRange = nullptr;
    endRange = nullptr;
}
