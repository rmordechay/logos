#include "loops/LgsRangeLoop.h"

#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsVarDec.h"

#include <LgsStack.h>
#include <types/LgsInt.h>

int LgsRangeLoop::loopSize() {
    const int rangeStartValue = dynamic_cast<LgsIntConst*>(rangeStart)->value;
    const int rangeEndValue = dynamic_cast<LgsIntConst*>(rangeEnd)->value;
    return rangeEndValue - rangeStartValue;
}

void LgsRangeLoop::setIRBody(CodeGenMetadata* metadata) {
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(iValue);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
    stmtBlock->getIRValue(metadata);
}
