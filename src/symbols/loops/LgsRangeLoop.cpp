#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsLLVM& codeGen) {
    return startRange->IRValue;
}

Value* LgsRangeLoop::loopEnd(LgsLLVM& codeGen) {
    return endRange->IRValue;
}

LgsRangeLoop::~LgsRangeLoop() {
    if (endRange) {
        delete endRange;
        endRange = nullptr;
    }
}
