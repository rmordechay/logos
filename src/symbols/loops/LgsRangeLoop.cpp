#include "loops/LgsRangeLoop.h"

#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsVarDec.h"

#include <LgsStack.h>
#include <types/LgsInt.h>

int LgsRangeLoop::loopStart() {
    return rangeStart->asIntConst()->value;
}

int LgsRangeLoop::loopEnd() {
    return rangeEnd->asIntConst()->value;
}

void LgsRangeLoop::setIRBody(CodeGenMetadata* metadata) {
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(iValue);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
}
