#include "loops/LgsLoopVar.h"
#include "LgsType.h"
#include "unary/LgsArrayIndex.h"

#include <exprs/LogosExpr.h>

Value* LgsLoopVar::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LgsLoopVar::~LgsLoopVar() {
    delete type;
    delete element;
}
