#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"
#include <LgsStack.h>

Value* LgsRangeLoop::loopStart(CodeGenMetadata* metadata) {
    return rangeStart->getIRValue(metadata);
}

Value* LgsRangeLoop::loopEnd(CodeGenMetadata* metadata) {
    return rangeEnd->getIRValue(metadata);
}

void LgsRangeLoop::setIRLoopVariable(CodeGenMetadata* metadata) {
    const auto loopVar = loopVars[0];
    loopVar->expr->setIRValue(iValue);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}