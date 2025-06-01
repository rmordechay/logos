#include "loops/LgsRangeLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(CodegenMetadata* metadata) {
    return rangeStart->getIRValue(metadata);
}

Value* LgsRangeLoop::loopEnd(CodegenMetadata* metadata) {
    return rangeEnd->getIRValue(metadata);
}

void LgsRangeLoop::setIRLoopVars(CodegenMetadata* metadata) {
    const auto loopVar = loopVars[0];
    const auto iValue = metadata->builder.CreateLoad(i32Ty, iPtr);
    loopVar->expr->setIRValue(iValue);
}

void LgsRangeLoop::setIRIterable(CodegenMetadata* metadata) {
    assert(false);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}
