#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsRuntime* runtime) {
    return rangeStart->getIRValue(runtime);
}

Value* LgsRangeLoop::loopEnd(LgsRuntime* runtime) {
    return rangeEnd->getIRValue(runtime);
}

void LgsRangeLoop::setIRLoopVars(LgsRuntime* runtime) {
    const auto loopVar = loopVars[0];
    const auto iValue = builder.CreateLoad(i32Ty, iPtr);
    loopVar->expr->setIRValue(iValue);
}

void LgsRangeLoop::setIRIterable(LgsRuntime* runtime) {
    assert(false);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}
