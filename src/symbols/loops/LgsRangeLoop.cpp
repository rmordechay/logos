#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsLLVMGen& cg) {
    return startRange->IRValue;
}

Value* LgsRangeLoop::loopEnd(LgsLLVMGen& cg) {
    return endRange->IRValue;
}

LgsRangeLoop::~LgsRangeLoop() {
    if (endRange) {
        delete endRange;
        endRange = nullptr;
    }
}
