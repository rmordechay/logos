#include "LgsValue.h"
#include "funcs/LgsFunc.h"

Value* LgsValue::loadIR(LgsLLVM& codeGen) {
    assert(IRValue);
    return IRValue;
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

void LgsValue::setDebugValue(LgsLLVM& codeGen) {
    assert(0);
}

DILocation* LgsValue::getDebugLoc(LgsLLVM& codeGen) const {
    return DILocation::get(
        codeGen.context,
        location.lineStart,
        location.posInLine,
        codeGen.diProgram,
        codeGen.diProgram->getScope()
    );
}