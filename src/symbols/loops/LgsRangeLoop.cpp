#include "loops/LgsRangeLoop.h"

#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsVarDec.h"

#include <LgsStack.h>
#include <types/primitives/LgsInt.h>

int LgsRangeLoop::loopStart() {
    return rangeStart->asIntConst()->value;
}

int LgsRangeLoop::loopEnd() {
    return rangeEnd->asIntConst()->value;
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}

void LgsRangeLoop::setIRLoopVariable(CodeGenMetadata* metadata) {
    const auto loopVar = loopVars[0];
    loopVar->expr->setIRValue(iValue);
    metadata->lgsStack.addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
}
