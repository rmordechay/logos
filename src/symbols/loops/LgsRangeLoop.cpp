#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(CodeGenMetadata* metadata) {
    return rangeStart->getIRValue(metadata);
}

Value* LgsRangeLoop::loopEnd(CodeGenMetadata* metadata) {
    return rangeEnd->getIRValue(metadata);
}

void LgsRangeLoop::setIRLoopVars(CodeGenMetadata* metadata) {
    const auto loopVar = loopVars[0];
    const auto iValue = metadata->builder.CreateLoad(i32Ty, iPtr);
    loopVar->expr->setIRValue(iValue);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}