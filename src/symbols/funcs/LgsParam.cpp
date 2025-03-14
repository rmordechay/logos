#include "funcs/LgsParam.h"

#include "LgsExpr.h"

Value* LgsParam::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LgsParam::~LgsParam() {
    if (expr) {
        delete expr;
    }
}
