#include "LgsValue.h"
#include "funcs/LgsFunc.h"

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

Value* LgsValue::getIRValue(LgsCodeGen* codeGen) {
    if (IRValue) return IRValue;
    createIRValue(codeGen);
    assert(IRValue);
    return IRValue;
}

void LgsValue::getDebugValue(LgsCodeGen* codeGen) {
    assert(0);
}

std::string LgsValue::format(std::string& indentStr) {
    assert(0);
}
