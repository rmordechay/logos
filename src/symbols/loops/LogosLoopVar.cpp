#include "loops/LogosLoopVar.h"
#include "LogosType.h"
#include "unary/LogosArrayIndex.h"

#include <exprs/LogosExpr.h>

Value* LogosLoopVar::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LogosLoopVar::~LogosLoopVar() {
    delete type;
    delete element;
}
