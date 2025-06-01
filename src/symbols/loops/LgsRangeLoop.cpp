#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(Module* module) {
    return rangeStart->getIRValue(module);
}

Value* LgsRangeLoop::loopEnd(Module* module) {
    return rangeEnd->getIRValue(module);
}

void LgsRangeLoop::setIRLoopVars(Module* module) {
    const auto loopVar = loopVars[0];
    const auto iValue = builder.CreateLoad(i32Ty, iPtr);
    loopVar->expr->setIRValue(iValue);
}

void LgsRangeLoop::setIRIterable(Module* module) {
    assert(false);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}
