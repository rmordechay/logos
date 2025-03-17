#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"

Value* LgsParam::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LgsParam::~LgsParam() {
    if (expr) {
        delete expr;
    }
}
