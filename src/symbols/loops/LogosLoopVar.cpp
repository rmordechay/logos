#include "loops/LogosLoopVar.h"
#include "LogosType.h"
#include <exprs/LogosExpr.h>

Value* LogosLoopVar::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LogosLoopVar::~LogosLoopVar() {
    delete type;
    delete expr;
}
