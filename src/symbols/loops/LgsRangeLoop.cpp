#include "loops/LgsRangeLoop.h"

#include "logos/LgsRuntime.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsRuntime* runtime) {
    return rangeStart->getIRValue(runtime);
}

Value* LgsRangeLoop::loopEnd(LgsRuntime* runtime) {
    return rangeEnd->getIRValue(runtime);
}

void LgsRangeLoop::setIRIterable(LgsRuntime* runtime) {

}

void LgsRangeLoop::setIRLoopVars(LgsRuntime* runtime) {
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}
