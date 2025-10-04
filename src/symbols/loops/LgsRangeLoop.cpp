#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsLLVMGen& cg) {
    return startRange->loadIR(cg);
}

Value* LgsRangeLoop::loopEnd(LgsLLVMGen& cg) {
    return endRange->loadIR(cg);
}

LgsRangeLoop::~LgsRangeLoop() {
    if (endRange) {
        delete endRange;
        endRange = nullptr;
    }
}
