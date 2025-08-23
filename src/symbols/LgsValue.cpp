#include "LgsValue.h"
#include "funcs/LgsFunc.h"

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

void LgsValue::createDebugValue(LgsCodeGen* codeGen) {
    assert(0);
}