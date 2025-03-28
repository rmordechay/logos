#include "loops/LgsRangeLoop.h"

#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsVarDec.h"

#include <LgsStack.h>
#include <types/LgsInt.h>

int LgsRangeLoop::loopSize() {
    const int rangeStartValue = rangeStart->asIntConst()->value;
    const int rangeEndValue = rangeEnd->asIntConst()->value;
    return rangeEndValue - rangeStartValue;
}

void LgsRangeLoop::setIRBody(CodeGenMetadata* metadata) {
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(iValue);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
}
