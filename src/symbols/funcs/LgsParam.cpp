#include "funcs/LgsParam.h"

#include <LogosExpr.h>

Value* LgsParam::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LgsParam::~LgsParam() {
    if (expr) {
        delete expr;
    }
}
