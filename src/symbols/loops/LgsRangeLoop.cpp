#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

Value* LgsRangeLoop::loopStart(LgsLLVMGen& cg) {
    return startRange->loadIR(cg);
}

Value* LgsRangeLoop::loopEnd(LgsLLVMGen& cg) {
    return endRange->loadIR(cg);
}

LgsRangeLoop::~LgsRangeLoop() {
    freeExpr(startRange);
    freeExpr(endRange);
    startRange = nullptr;
    endRange = nullptr;
}
