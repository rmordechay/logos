#include "funcs/LogosParam.h"

#include <LogosExpr.h>

Value* LogosParam::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LogosParam::~LogosParam() {
    if (expr) {
        delete expr;
    }
}
